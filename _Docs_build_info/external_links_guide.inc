:orphan:

External Links Management Guide
===============================

This document explains how to manage external links in the Red Pitaya documentation.

Method 1: Using Sphinx extlinks Extension (Recommended)
-------------------------------------------------------

With the extlinks extension, you can create shortcuts for commonly used external links.

Usage examples:

**Red Pitaya Links:**

- :rp-web:`STEMlab 125-14 Gen 2 page <stemlab-125-14-gen2>` - Links to https://redpitaya.com/stemlab-125-14-gen2
- :rp-github:`RedPitaya` - Links to GitHub repository

**General Links:**

- :wikipedia:`FPGA` - Links to Wikipedia FPGA page
- :github:`RedPitaya` - Links to any GitHub repository
- :python-package:`numpy` - Links to PyPI package page


Method 2: RST Substitutions (Alternative)
------------------------------------------

You can also use RST substitutions for frequently used links. Add these to your RST files:

.. code-block:: rst

   .. |custom-link| replace:: `Custom Link <https://example.com/>`__
   .. |github-repo| replace:: `GitHub Repository <https://github.com/RedPitaya/RedPitaya>`__

Then use them in text like: |redpitaya| is an open-source project with a |github-repo|.

   .. |github-repo| replace:: `GitHub Repository <https://github.com/RedPitaya/RedPitaya>`__


Method 3: Global Substitutions (Advanced)
------------------------------------------

For links used across multiple files, you can define them in ``conf.py``:

.. code-block:: python

   rst_epilog = '''
   .. |redpitaya| replace:: `Red Pitaya <https://redpitaya.com/>`__
   .. |redpitaya-forum| replace:: `Red Pitaya Forum <https://forum.redpitaya.com/>`__
   '''

These global substitutions are already available: |redpitaya|, |redpitaya-forum|, |matplotlib|, etc.

Old method (for reference only)
--------------------------------

.. |Red Pitaya GitHub repository| raw:: html

    <a href="https://github.com/RedPitaya/RedPitaya/tree/master/deprecated" target="_blank">Red Pitaya GitHub repository - deprecated applications</a>



Configuration in conf.py
-------------------------

The current configuration includes:

.. code-block:: python

   # External Links configuration
   extlinks = {
       'rp-web': ('https://redpitaya.com/%s', 'Red Pitaya: %s'),
       'rp-github': ('https://github.com/RedPitaya/%s', 'GitHub: %s'),
       'rp-forum': ('https://forum.redpitaya.com/%s', 'Forum: %s'),
       'wikipedia': ('https://en.wikipedia.org/wiki/%s', 'Wikipedia: %s'),
       'github': ('https://github.com/%s', 'GitHub: %s'),
       'python-package': ('https://pypi.org/project/%s/', 'PyPI: %s'),
       'xilinx-doc': ('https://docs.xilinx.com/%s', 'Xilinx: %s'),
   }


Best Practices
--------------

1. **Use extlinks for frequently referenced sites** with variable paths
2. **Use direct links for one-off references**
3. **Keep link definitions in the central _links/link.py file**
4. **Update broken links centrally when needed**
5. **Use descriptive link text for accessibility**


Maintenance
-----------

To update external links:

1. Edit ``_links/link.py`` for the link definitions
2. Update ``conf.py`` if new extlinks patterns are needed
3. Test links periodically using ``sphinx-build -b linkcheck``


Link Checking
-------------

To check for broken links, run:

.. code-block:: bash

   sphinx-build -b linkcheck . _build/linkcheck

This will generate a report of any broken external links.
