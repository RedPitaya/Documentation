Red Pitaya original generation boards are factory-calibrated. Recalibration may be required after extended use, environmental changes, or when measurement accuracy degrades.

There are three ways to calibrate the board:

* :ref:`Calibration application <calibration_app>` — graphical interface accessible from the *System Tools* menu. Recommended for most users.
* :ref:`Calibration command line utility (calib) <calib_util>` — command line tool for scripted or advanced calibration workflows.
* :ref:`C++ or Python API commands <API_commands>` — programmatic access to calibration parameters.

For a full description of the calibration procedure, required equipment, and technical reference, please refer to the :ref:`Calibration documentation <calibration_app>`.

.. note::

    Original generation boards require 50 Ω terminators during calibration due to a mismatch in the impedance of fast analog inputs and outputs.
