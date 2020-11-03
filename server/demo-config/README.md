# Server setup for Kiwi Air Monitor

1. Install docker & docker compose on your server (for example a raspberry pi).
2. Copy the contents of this directory to the server.
3. run `docker-compose up -d` to start the servers
4. open `http://<ip or hostname of server>:3000/` and connect to Grafana
5. login with user `admin` and password `admin`. The UI will ask you to choose a new password.
6. Click on the `+` sign on the left and choose `Import`. Upload the `kiwi.json` file in this directory for a start of a dashboard.
