.. _ConnectSTEMlab:

#####################
Connect to Red Pitaya
#####################

This is the most common and recommended way of connecting and using your Red Pitaya boards.
Your LAN network must have DHCP settings enabled which is true with most local networks.
With this, a simple *plug and play* approach is enabled.
Having a Red Pitaya board connected to the local network will enable quick access to all Red Pitaya applications using only your web browser.

Follow these five simple steps to start using your Red Pitaya:

.. tabs::

   .. tab:: 125-10, 125-14, 122-16, 125-14 4-Input

      #. Update the Red Pitaya OS on the included SD card to the :ref:`latest version <prepareSD>`
      #. Insert the SD card into your Red Pitaya board

         .. figure:: SDcard/img/pitaya-quick-start-insert-sd-card.png
            :width: 400
            :align: center

      #. Connect your Red Pitaya board to the router

         .. figure:: connect/125_router.png
            :width: 400
            :align: center

      #. Connect the power supply to the Red Pitaya board
      #. Open your web browser and type ``rp-xxxxxx.local/`` into the address bar

         .. figure:: connect/125_stiker.png
            :width: 400
            :align: center

         .. figure:: connect/125_stiker_2.png
            :width: 400
            :align: center
   
   .. tab:: 250-12

      #. Update the Red Pitaya OS on the included SD card to the :ref:`latest version <prepareSD>`
      #. Insert the SD card into your Red Pitaya board

         .. figure:: SDcard/img/pitaya-quick-start-insert-sd-card.png
            :width: 400
            :align: center

      #. Connect your Red Pitaya board to the router

         .. figure:: connect/250_router.png
            :width: 400
            :align: center

      #. Connect the power supply to the Red Pitaya board
      #. Open your web browser and type ``rp-xxxxxx.local/`` into the address bar

         .. figure:: connect/250_stiker.png
            :width: 800
            :align: center

.. note::

   When updating the OS to 2.00 version from 1.04 or older (or downgrading from 2.00 to 1.04 or older), a factory reset of calibration parameters must be performed. Please open the Red Pitaya's web interface and head to **System => Calibration => Manual DC calibration**. Click on **Reset**, select **Factory**, and confirm the reset. For more details on calibration, please see the :ref:`Calibration application <calibration_app>`.

.. note::

   ``xxxxxx`` are the last six characters of the MAC address of your Red Pitaya board.
   The MAC address is written on the Ethernet connector.
    
After the **fifth step**, you will get a Red Pitaya main page, as shown below.

.. figure:: connect/connect-3.png
   :align: center

   Red Pitaya's main page user interface.

.. raw:: html

    <div style="position: relative; padding-bottom: 30.25%; overflow: hidden; max-width: 50%; margin-left:auto; margin-right:auto;margin-bottom: 20px;">
        <iframe src="https://www.youtube.com/embed/I21xyTCiZ-8" frameborder="0" allowfullscreen style="position: absolute; top: 0; left: 0; width: 100%; height: 100%;"></iframe>
    </div>


.. note::

    For any issues during setup, check :ref:`troubleshooting <faq>` or look on the |forum| for a solution.
    If you cannot find a solution, please write to support@redpitaya.com or post your problem on the forum, providing the following details:

       - Red Pitaya board model (STEMlab 125-14, SDRlab 122-16, SIGNALlab 250-12, etc.),
       - Is the board a variation of any board models (Low Noise, External Clock),
       - Red Pitaya OS version (bottom-right corner of the web interface),
       - Description of the problem in as much detail as possible,
       - Any other information you think might be relevant to the situation.


.. |forum| raw:: html

   <a href="https://forum.redpitaya.com/" target="_blank">forum</a>


================
Connection types
================

For detailed instructions on connection types, please check out the sections below:

.. toctree::
   :maxdepth: 2
   
   connect/connect

.. note::

   **Windows 7/8** users should install `Bonjour Print Services <https://downloads.redpitaya.com/tools/BonjourPSSetup.exe>`_,
   otherwise access to ``*.local`` addresses will not work.

   **Windows 10 or higher** already supports mDNS and DNS-SD, so there is no need to install additional software.

.. note::

   Access to the internet is only required when:

   *   using the OS update application,
   *   installing applications from the marketplace.
