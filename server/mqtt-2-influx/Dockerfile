FROM --platform=$BUILDPLATFORM golang:1.15-alpine as build-env
# we build on native platform using cross compilation build into golang
# this saves quite some time since we can avoid emulating armv6
ARG TARGETPLATFORM
# copy the TARGETPLATFORM parser
COPY --from=tonistiigi/xx:golang / / 
WORKDIR /go/src/app
ADD . /go/src/app
RUN CGO_ENABLED=0 go build -o /go/bin/mqtt-2-influx


FROM alpine
RUN apk --no-cache add ca-certificates
WORKDIR /
COPY --from=build-env /go/bin/mqtt-2-influx /
ENTRYPOINT ["/mqtt-2-influx"]
