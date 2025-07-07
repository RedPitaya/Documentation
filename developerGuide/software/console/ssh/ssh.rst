.. _ssh:

###############################
Establish remote SSH connection
###############################

Access information for SSH connection:

* Username: ``root``
* Password: ``root``

If you are unable to connect, check that Red Pitaya is connected to your :ref:`local network <faq_isConnected>`.

Connection instructions are available for:

.. contents::
    :local:
    :backlinks: none
    :depth: 1


Windows 10
==========

On Windows you can establish an SSH connection directly through the Command Prompt or use a program like |Putty| or |WinScp|. Here we will discuss both options.

.. |PuTTy| raw:: html

   <a href="http://www.putty.org" target="_blank">PuTTy</a>

.. |WinScp| raw:: html

   <a href="https://winscp.net/eng/index.php" target="_blank">WinScp</a>

Command Prompt
---------------

To establish an SSH connection through the Command Prompt, first open the Command Prompt console window (search for "command prompt" in Windows Search).

Enter the following command:

.. tabs::

    .. tab:: IP

        .. code-block:: console
        
            ssh root@<Red Pitaya IP address>

    .. tab:: Local address

        .. code-block:: console
        
            ssh root@rp-xxxxxx.local

If you attempt to connect to Red Pitaya for the first time, a security alert will display asking you to confirm the connection (type "yes").
At this time, the ssh-key will be added to the registry on your computer.

Next, the console will ask for a password (``root``).

After the password was entered, the login text will appear. Here is a picture of the whole exchange:

.. figure:: img/ssh_console_win.png
    :width: 600 px
    :align: center

The last command prompt/terminal line should read as “root@rp-xxxxxx:~#“ (the default home directory on Red Pitaya is /root).

.. note::

    After updating the OS or after some time has passed since the last SSH connection, you might get the following message when trying to establish an SSH connection.

    .. code-block:: console

        @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        @    WARNING: REMOTE HOST IDENTIFICATION HAS CHANGED!     @
        @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        IT IS POSSIBLE THAT SOMEONE IS DOING SOMETHING NASTY!
        Someone could be eavesdropping on you right now (man-in-the-middle attack)!
        It is also possible that the RSA host key has just been changed.
        The fingerprint for the RSA key sent by the remote host is
        06:ea:f1:f8:db:75:5c:0c:af:15:d7:99:2d:ef:08:2a.
        Please contact your system administrator.
        Add correct host key in /home/user/.ssh/known_hosts to get rid of this message.
        Offending key in /home/user/.ssh/known_hosts:4
        RSA host key for domain.com has changed and you have requested strict checking.
        Host key verification failed.

    
    Do not worry, nothing is wrong with your Red Pitaya. The problem is that the Red Pitaya identification key has changed. To fix this use the following code:

    .. code-block:: console

        ssh-keygen -R rp-xxxxxx.local

    And try to establish the SSH connection again.

    Alternatively, open Explorer and go to **C:/Users/<your-username>/.ssh** and open the **known_hosts** file. Delete all lines containing *rp-xxxxxx.local*.


Connection via a program (PuTTy, WinSCP, ...)
-----------------------------------------------

For this example, the PuTTy and WinSCP tools were used on Windows 11.
Run PuTTy/WinSCP and enter the Red Pitaya's IP (or .local) address into the **Host Name (or IP address)** field.

.. figure:: img/ssh_putty_config.png
   :width: 600
   :align: center

   PuTTy SSH connection settings.

.. figure:: img/ssh_winscp_config.png
   :width: 600
   :align: center

   WinSCP SSH connection settings.

Make sure the port number is set to 22. Fill the "User name" as ``root`` on WinSCP. Then select **Open/Login**.

Input password ``root``.

If you attempt to connect to Red Pitaya for the first time, a security alert will pop up asking you to confirm the connection.
At this time, the ssh-key will be added to the registry on your computer. A command prompt pops up after login is successful.

.. figure:: img/ssh_putty_alert.png
   :width: 600
   :align: center

When connected to RP via SSH, you get the following command prompt screen:

.. figure:: img/ssh_putty.png
   :width: 600
   :align: center

   SSH connection via PuTTy

.. figure:: img/ssh_winscp_con.png
   :width: 600
   :align: center

   SSH connection via WinSCP

The last command prompt/terminal line should read as “root@rp-xxxxxx:~#“ (the default home directory on Red Pitaya is /root).


Linux
=====

Start Terminal and type (replace the IP address with the right one):

.. code-block:: shell-session

   user@ubuntu:~$ ssh root@192.168.1.100
   root@192.168.1.100's password: root
   Red Pitaya GNU/Linux/Ecosystem version 0.90-299
   redpitaya>

.. figure:: img/linux_terminal.png
   :align: center


macOS
=====

Run terminal **Launchpad → Other → Terminal** and type (replace the IP address with the right one):

.. code-block:: shell-session
  
   localhost:~ user$ ssh root@192.168.1.100
   root@10.0.3.249's password: root
   Red Pitaya GNU/Linux/Ecosystem version 0.90-299
   redpitaya>
