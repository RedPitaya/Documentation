:orphan:

External Links Test
===================

This document demonstrates the different ways to use external links in the Red Pitaya documentation.

Method 1: Using extlinks shortcuts
-----------------------------------

These use the configured extlinks from conf.py:

- Visit :rp-web:`the main website <>`
- Check out :rp-github:`RedPitaya`
- Ask questions on :rp-forum:`category/general-discussion`
- Look up :wikipedia:`Field-programmable_gate_array`
- Install :python-package:`numpy`

Method 2: Using global substitutions
-------------------------------------

These use the global substitutions defined in rst_epilog:

- Learn more about |redpitaya| and its capabilities
- Visit the |redpitaya-github| repository
- Join the |redpitaya-forum| community
- Shop at the |redpitaya-store|
- Read the |sphinx-docs| for documentation tips
- Use |python| for programming examples
- Analyze data with |numpy| and |matplotlib|
- Design FPGA code with |vivado| from |xilinx|
- Send commands using |scpi| protocol

Method 3: Direct links (traditional)
-------------------------------------

For one-off links or when you need specific link text:

- `Red Pitaya Official Website <https://redpitaya.com/>`__
- `Red Pitaya GitHub Repository <https://github.com/RedPitaya/RedPitaya>`__
- `Red Pitaya Community Forum <https://forum.redpitaya.com/>`__

Benefits of centralized link management
----------------------------------------

1. **Easy maintenance**: Update a URL in one place, changes everywhere
2. **Consistency**: Same link text and formatting across documentation
3. **Performance**: Reduces duplication and file size
4. **Link checking**: Easier to validate all external links
5. **Flexibility**: Multiple methods for different use cases

Best practice recommendations
-----------------------------

1. Use **extlinks** for sites with variable paths (e.g., GitHub repos, Wikipedia articles)
2. Use **global substitutions** for frequently referenced sites with fixed URLs
3. Use **direct links** for one-off references or when you need custom link text
4. Keep all link definitions in the ``_links/link.py`` file for easy maintenance
