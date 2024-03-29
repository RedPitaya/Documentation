.. _daq_server_app:

*********************
Red Pitaya DAQ Server
*********************

This application allows for the continuous generation and measurement of signals with up to 15.625 MS/s, which is not possible with the standard image of the RedPitaya.
In addition, the software allows the synchronisation of a cluster of multiple RedPitayas (compatible with |X-channel|). This project contains the following parts:

    -   Alpine Linux image for the RedPitaya
    -   FPGA image
    -   Client library (implemented in C) that can be used on the RedPitaya
    -   SCPI Server for accessing the functionality over TCP/IP
    -   SCPI Clients to access the server
    
Here you can find out more about the Red Pitaya DAQ server:

    -   |DAQ server Github|
  
.. |X-channel| raw:: html

   <a href="https://redpitaya.com/product/stemlab-125-14-x-channel-system/" target="_blank">X-channel</a>
   
.. |DAQ server Github| raw:: html

   <a href="https://tknopp.github.io/RedPitayaDAQServer.jl/dev/" target="_blank">DAQ server Github</a>
