// SPDX-License-Identifier: GPL-3.0-or-later
// kiwi-config configures kiwi air monitor instances
// Copyright (C) 2020 Davy Landman, Swat.engineeering
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

package main

import (
	"errors"
	"io/ioutil"
	"log"
	"os"
	"os/exec"

	"crypto"
	"crypto/md5"
	"crypto/rand"
	"crypto/rsa"
	"crypto/sha256"
	"crypto/x509"

	"encoding/hex"

	"github.com/bmatcuk/doublestar/v2"
	"github.com/manifoldco/promptui"
	"github.com/pelletier/go-toml"
)

type kiwiConfig struct {
	Features features
	Ota      ota
	Mqtt     mqtt
	Wifi     []wifi
}

type features struct {
	Ota         bool
	mqtt        bool
	pressence   bool
	co2         bool
	temperature bool
}

type ota struct {
	URL string
	Key string
}

type mqtt struct {
	Server   string
	Port     int
	Username string
	Password string
}

type wifi struct {
	SSID     string
	Password string
}

func pio(args ...string) *exec.Cmd {
	//.platformio\penv\Scripts\platformio.exe`
	run := exec.Command("platformio", args...)
	run.Stderr = os.Stderr
	run.Stdout = os.Stdout
	return run
}

func (config *kiwiConfig) load() error {
	fileName, err := getConfigFilename()
	if err != nil {
		return err
	}
	source, err := os.Open(fileName)
	if err != nil {
		return err
	}
	defer source.Close()
	return toml.NewDecoder(source).Decode(config)
}

var selectedConfigFile = ""

func getConfigFilename() (string, error) {
	if selectedConfigFile == "" {
		files, err := doublestar.Glob("./**/*.toml")
		if err != nil {
			return "", err
		}
		if len(files) < 1 {
			return "", errors.New("No .toml files found in the current working directory")
		}
		filePick := promptui.Select{
			Label: "Choose configuration file",
			Items: files,
		}
		selected, _, err := filePick.Run()
		if err != nil {
			return "", err
		}
		selectedConfigFile = files[selected]
	}
	return selectedConfigFile, nil
}

func compileKiwiFirmware() error {
	//conf, err := loadConfig();
	return nil
}

func flashKiwi() error {
	return nil

}

func nonnill(errs ...error) error {
	for _, e := range errs {
		if e != nil {
			return e
		}
	}
	return nil
}

func sign(keyFile string, firmwareFile string) (string, error) {
	firmware, err := ioutil.ReadFile(firmwareFile)
	if err != nil {
		return "", err
	}
	md5Sum := md5.Sum(firmware)
	sha256Sum := sha256.Sum256(firmware)

	keyDer, err := ioutil.ReadFile(keyFile)
	if err != nil {
		return "", err
	}
	privateKey, err := x509.ParsePKCS1PrivateKey(keyDer)
	if err != nil {
		return "", err
	}
	signature, err := rsa.SignPKCS1v15(rand.Reader, privateKey, crypto.SHA256, sha256Sum[:])
	if err != nil {
		return "", err
	}
	output, err := os.Create("update.bin")
	if err != nil {
		return "", err
	}
	defer output.Close()

	_, err1 := output.Write(firmware)
	_, err2 := output.Write(signature)
	_, err3 := output.Write([]byte{0x00, 0x01, 0x00, 0x00}) // 256 bytes hash
	return hex.EncodeToString(md5Sum[:]), nonnill(err1, err2, err3)
}

func prepareOTA() error {
	if err := compileKiwiFirmware(); err != nil {
		return err
	}
	var conf kiwiConfig
	if err := conf.load(); err != nil {
		return err
	}
	md5sum, err := sign(conf.Ota.Key, "firmware.bin")
	if err != nil {
		return err
	}
	log.Printf("Upload the update.bin file to the %s server and send: %s as the new firmware version", conf.Ota.URL, md5sum)
	return nil

}
func generateKey() error {
	key, err := rsa.GenerateKey(rand.Reader, 2048)
	if err != nil {
		return err
	}

	if err := ioutil.WriteFile("ota-key.rsa", x509.MarshalPKCS1PrivateKey(key), 0700); err != nil {
		return err
	}
	log.Println("Written ota-key.rsa, please refer to this file in your config. Never share this file!")
	return nil
}

func main() {
	operation := promptui.Select{
		Label: "Choose Kiwi Air Monitor action",
		Items: []string{
			"Compile new kiwi firmware",
			"Flash Kiwi",
			"Prepare OTA",
			"Generate signing key",
		},
	}
	selected, _, err := operation.Run()
	if err != nil {
		log.Fatal("Error picking operation", err)
	}
	switch selected {
	case 0:
		err = compileKiwiFirmware()
	case 1:
		err = flashKiwi()
	case 2:
		err = prepareOTA()
	case 3:
		err = generateKey()
	}
	if err != nil {
		log.Fatal(err)
	}
}
