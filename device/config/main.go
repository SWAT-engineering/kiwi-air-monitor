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

	"crypto/rand"
	"crypto/rsa"
	"crypto/x509"
	"encoding/pem"

	"github.com/bmatcuk/doublestar/v2"
	"github.com/manifoldco/promptui"
	"github.com/pelletier/go-toml"
)

type kiwiConfig struct {
	Feat features
	Ota  ota
	Mqtt mqtt
	Wifi []wifi
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
func prepareOTA() error {
	if err := compileKiwiFirmware(); err != nil {
		return err
	}
	var conf kiwiConfig
	if err := conf.load(); err != nil {
		return err
	}
	log.Printf("%+v", conf)
	return nil

}
func generateKey() error {
	// Generate RSA key.
	key, err := rsa.GenerateKey(rand.Reader, 2048)
	if err != nil {
		return err
	}

	// Encode private key to PKCS#1 ASN.1 PEM.
	keyPEM := pem.EncodeToMemory(
		&pem.Block{
			Type:  "RSA PRIVATE KEY",
			Bytes: x509.MarshalPKCS1PrivateKey(key),
		},
	)

	// Write private key to file.
	if err := ioutil.WriteFile("ota-key.rsa", keyPEM, 0700); err != nil {
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
