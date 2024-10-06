# IOT_UBUNTU_Terminal_VPN_Proxy

1. Install every Proxy On Ur Host Device
2. Set ur Device Avialable IP & Port & save it 
3. Turn on ur SIM Hotspot
4. Connect to Te host WIFI
5. Set ur Host IP As Network Proxy , So know u have Browser VMN on ur UBUNTU Linux OS.
6. Open One Terminal
7. :~$ echo 'export https_proxy="http://HostIP:Port"' >> ~/.bashrc
8. :~$ echo 'export http_proxy="http://http://HostIP:Port"' >> ~/.bashrc
9. ~$ source ~/.bashrc
10. try to test Terminal VPN via  ~$ curl -I https://www.youtube.com/
11. Bingooooooooo! :-)
