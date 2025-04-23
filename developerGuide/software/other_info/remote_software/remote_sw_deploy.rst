.. _remote_software_delpoy:

###########################
Remote software deployment
###########################

The :ref:`Software update manager <software_update_manager>` can be configured to upload custom software from a user-defined server.

To implement this, modification of the following two files from Red Pitaya Github is required, where the Red Pitaya download server ("http://downloads.redpitaya.com/downloads/$1") is replaced with the user-defined server address.

- |list.sh|
- |download.sh|

.. |list.sh| raw:: html

  <a href="https://github.com/RedPitaya/RedPitaya/blob/master/apps-tools/updater/scripts/list.sh" target="_blank">list.sh</a>

.. |download.sh| raw:: html

  <a href="https://github.com/RedPitaya/RedPitaya/blob/master/apps-tools/updater/scripts/download.sh" target="_blank">download.sh</a>
