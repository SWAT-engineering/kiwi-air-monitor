FROM golang:1.15-alpine as build-env
WORKDIR /go/src/app
ADD . /go/src/app
RUN go build -o /go/bin/mqtt-2-influx


FROM alpine
RUN apk --no-cache add ca-certificates
WORKDIR /app
COPY --from=build-env /go/bin/mqtt-2-influx /app/
ENTRYPOINT /app/mqtt-2-influx
