# fake kiwi air monitor

This generator can be used to generate messages on your MQTT server as if a real Kiwi Air Monitor is running.

After installing golang on your computer, you can run this program like this:

```
go run main.go
```

There are two parameters:

```
  -clients int
        Specifiy the amount of clients to generate (default 2)
  -mqttURL string
        Mqtt server to connect to (default "mqtt://localhost:8883/")
```