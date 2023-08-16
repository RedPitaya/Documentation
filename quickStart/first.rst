.. _ConnectSTEMlab:

Connect to Red Pitaya
#####################

This is the most common and recommended way of
connecting and using your Red Pitaya boards.
Your LAN network needs to have DHCP settings enabled,
which is the case with the majority of local networks.
With this, a simple *plug and play* approach is enabled.
Having a Red Pitaya board connected to the local network
will enable quick access to all Red Pitaya applications
using only your web browser.

Simply follow this 3 simple steps:

.. tabs::

   .. tab:: 125-10, 125-14, 122-16, 125-14 4-Input

      #. Connect your Red Pitaya board to the router

         .. figure:: connect/125_router.png
            :width: 50%
            :align: center

      #. Connect the power supply to the Red Pitaya board
      #. Open your web browser and type ``rp-xxxxxx.local/`` into the address bar

         .. figure:: connect/125_stiker.png
            :width: 50%
            :align: center

         .. figure:: connect/125_stiker_2.png
            :width: 50%
            :align: center
   
   .. tab:: 250-12

      #. Connect your Red Pitaya board to the router

         .. figure:: connect/250_router.png
            :width: 50%
            :align: center

      #. Connect the power supply to the Red Pitaya board
      #. Open your web browser and type ``rp-xxxxxx.local/`` into the address bar

         .. figure:: connect/250_stiker.png
            :width: 90%
            :align: center
       
.. note::

   ``xxxxxx`` are the last 6 characters of the MAC address of your Red Pitaya board.
   The MAC address is written on the Ethernet connector.
    
After the **third step** you will get a Red Pitaya main page as shown below.

.. figure:: connect/connect-3.png
   :align: center

   Red Pitaya's main page user interface.

.. raw:: html

    <div style="position: relative; padding-bottom: 30.25%; overflow: hidden; max-width: 50%; margin-left:auto; margin-right:auto;margin-bottom: 20px;">
        <iframe src="https://www.youtube.com/embed/I21xyTCiZ-8" frameborder="0" allowfullscreen style="position: absolute; top: 0; left: 0; width: 100%; height: 100%;"></iframe>
    </div>


.. note::

    For any issues during setup, check :ref:`troubleshooting <faq>` or check the |forum| for a solution.
    If you cannot find a solution, please post your problem, providing as much detail as possible.

.. |forum| raw:: html

   <a href="https://forum.redpitaya.com/" target="_blank">forum</a>


.. note:: 

    For arranging other types of connections (wireless, direct ethernet connection), use the  
    :ref:`Network Manager <networkManager>`.


.. note::

   **Windows 7/8** users should install `Bonjour Print Services <https://downloads.redpitaya.com/tools/BonjourPSSetup.exe>`_,
   otherwise access to ``*.local`` addresses will not work.

   **Windows 10** already supports mDNS and DNS-SD,
   so there is no need to install additional software.

.. note::

   Access to the internet is only required when:

   * upgrading Red Pitaya OS,
   * installing applications from the marketplace.
