# -*- coding: utf-8 -*-

import sys
import os
import datetime

on_rtd = os.environ.get('READTHEDOCS', None) == 'True'

sys.path.append(os.path.abspath('.') + '/_extensions')
sys.path.append(os.path.abspath('.')+ '/_links')
sys.path.append(os.path.abspath('.'))

from _links.link import EXTERNAL_LINKS, SPHINX_EXTLINKS

# Define custom inline roles before each document is parsed.  The upstream
# epilog also contains these definitions, but Chinese text next to a role can
# make docutils resolve the role before reaching the epilog.
rst_prolog = """
.. role:: blue(strong)
    :class: text-bold-blue

.. role:: orange(strong)
    :class: text-bold-orange

.. role:: green(strong)
    :class: text-bold-green

.. role:: red(strong)
    :class: text-bold-red

"""

needs_sphinx = '8.0'            # Minimum Sphinx version required to build the documentation

# Sphinx extensions
extensions = [
    'sphinx_rtd_theme',
    'sphinx.ext.autodoc',
    'sphinx.ext.napoleon',
    'sphinx.ext.mathjax',
    'sphinx.ext.todo',
    'sphinx.ext.intersphinx',
    'sphinx.ext.viewcode',
    'sphinx.ext.githubpages',
    'sphinx.ext.extlinks',
    'sphinx_tabs.tabs',
    'sphinx_copybutton',
    'sphinx_design',
    'notfound.extension',
    'sphinxext.rediraffe',
    'github',
    'myst_parser'
]

# MyST Parser
myst_enable_extensions = [
    "colon_fence",
    "deflist",
    "html_admonition",
    "html_image",
    "linkify",
    "replacements",
    "smartquotes",
    "substitution",
    "tasklist",
]

extlinks = SPHINX_EXTLINKS

copybutton_prompt_text = r">>> |\.\.\. |\$ |In \[\d*\]: | {2,5}\.\.\.: | {5,8}: "
copybutton_prompt_is_regexp = True

# Shared reST substitutions and roles.
rst_epilog = """
.. ============================================================================
.. CENTRALIZED EXTERNAL LINKS - Automatically available in all RST files
.. To use: |link_name| in your text
.. To update: Edit _links/link.py, then links update everywhere automatically
.. ============================================================================

.. role:: blue(strong)
    :class: text-bold-blue

.. role:: orange(strong)
    :class: text-bold-orange

.. role:: green(strong)
    :class: text-bold-green

.. role:: red(strong)
    :class: text-bold-red

.. Red Pitaya Infrastructure
.. |redpitaya| replace:: `Red Pitaya <{redpitaya_website}>`__
.. |redpitaya-github| replace:: `Red Pitaya GitHub <{redpitaya_github}>`__
.. |redpitaya-forum| replace:: `Red Pitaya Forum <{redpitaya_forum}>`__
.. |redpitaya-store| replace:: `Red Pitaya Store <{redpitaya_store}>`__
.. |redpitaya-downloads| replace:: `Red Pitaya Downloads <{redpitaya_downloads}>`__
.. |redpitaya-contact| replace:: `Red Pitaya Contact <{redpitaya_contact}>`__

.. Development Tools - Windows
.. |WinSCP| replace:: `WinSCP <{winscp}>`__
.. |PuTTy| replace:: `PuTTy <{putty}>`__
.. |FTDI-driver| replace:: `FTDI driver <{ftdi_driver}>`__

.. Development Tools - Cross-platform
.. |VSCode| replace:: `Visual Studio Code <{vscode}>`__
.. |vscode-workspace| replace:: `workspace <{vscode_workspace}>`__
.. |vscode-tutorials| replace:: `tutorials <{vscode_tutorials}>`__
.. |vscode-venv| replace:: `virtual environment <{vscode_python_env}>`__

.. SD Card Tools
.. |balenaEtcher| replace:: `balenaEtcher <{balena_etcher}>`__
.. |ApplePi-Baker| replace:: `ApplePi-Baker <{applepi_baker}>`__

.. Python Ecosystem
.. |python| replace:: `Python <{python_downloads}>`__
.. |numpy| replace:: `NumPy <{numpy}>`__
.. |matplotlib| replace:: `Matplotlib <{matplotlib}>`__
.. |scipy| replace:: `SciPy <{scipy}>`__
.. |PyVISA| replace:: `PyVISA <{pyvisa}>`__
.. |PyVISA-py| replace:: `PyVISA-py <{pyvisa_py}>`__

.. Documentation Tools
.. |sphinx-docs| replace:: `Sphinx Documentation <{sphinx_docs}>`__
.. |Markdown| replace:: `Markdown <{markdown}>`__
.. |Markdown-Daring| replace:: `Markdown <{markdown_daringfireball}>`__
.. |MathJax| replace:: `MathJax <{mathjax}>`__
.. |JSON| replace:: `JSON <{json}>`__
.. |JSON-wiki| replace:: `JSON <{json_wiki}>`__
.. |nbconvert| replace:: `nbconvert <{nbconvert}>`__

.. Linux Tools
.. |minicom| replace:: `Minicom <{minicom}>`__
.. |screen| replace:: `screen <{screen}>`__
.. |WSL| replace:: `Windows Subsystem for Linux <{wsl}>`__
.. |WSL-USB| replace:: `Connect USB devices <{wsl_usb}>`__

.. Hardware Vendors & FPGA Tools
.. |xilinx| replace:: `Xilinx <{xilinx}>`__
.. |vivado| replace:: `Vivado <{vivado}>`__
.. |Vivado-downloads| replace:: `AMD's downloads webpage <{vivado_downloads}>`__
.. |Vivado-downloads-archive| replace:: `AMD Xilinx Vivado SDK Downloads Page <{vivado_downloads_archive}>`__
.. |AMD-login| replace:: `AMD Registration Page <{amd_login}>`__
.. |Xilinx-device-tree| replace:: `GitHub - Xilinx Device Tree <{xilinx_device_tree}>`__
.. |TI| replace:: `Texas Instruments <{texas_instruments}>`__
.. |Microchip| replace:: `Microchip <{microchip}>`__
.. |Seeed-Grove| replace:: `Seeed® <{seeed_grove}>`__
.. |Seeed-temp| replace:: `Temperature sensor <{seeed_temp_sensor}>`__
.. |Seeed-motion| replace:: `Motion sensor <{seeed_motion_sensor}>`__
.. |Seeed-touch| replace:: `Touch sensor <{seeed_touch_sensor}>`__
.. |Seeed-button| replace:: `Button <{seeed_button}>`__
.. |Seeed-switch| replace:: `Switch <{seeed_switch}>`__
.. |Seeed-tilt| replace:: `Tilt <{seeed_tilt}>`__
.. |Seeed-potentiometer| replace:: `Potentiometer <{seeed_potentiometer}>`__

.. Communication Protocols
.. |scpi| replace:: `SCPI <{scpi_standard}>`__
.. |MCP2542-Click| replace:: `MCP2542 Click Board <{mikroe_mcp2542}>`__
.. |CSS-CAN| replace:: `CSS Electronics <{css_electronics_can}>`__
.. |SMBUS-specs| replace:: `SMBUS specifcations <{smbus_specs}>`__

.. Third-party Red Pitaya Projects
.. |pavel-demin-notes| replace:: `Pavel Demin's Red Pitaya Notes <{pavel_demin_notes}>`__
.. |Linien| replace:: `Linien <{linien}>`__
.. |PyRPL| replace:: `PyRPL <{pyrpl}>`__
.. |Marcelo-Lock-in| replace:: `Lock-in+PID <{marcelo_lock_in}>`__
.. |jupyter-cadquery| replace:: `Jupyter CadQuery <{jupyter_cadquery}>`__

.. Media & Community Tools
.. |Audacity| replace:: `Audacity <{audacity}>`__

.. Wikipedia & General Reference
.. |wiki-dhcp| replace:: `more info <{wiki_dhcp}>`__
.. |wiki-network-socket| replace:: `socket communication <{wiki_network_socket}>`__
.. |wiki-arbitrary-waveform| replace:: `arbitrary waveform generator <{wiki_arbitrary_waveform}>`__
.. |wiki-subnet| replace:: `Wikipedia subnetwork <{wiki_subnet}>`__
.. |wiki-ip-address| replace:: `Wikipedia IP address <{wiki_ip_address}>`__
.. |WikiHow-refresh| replace:: `link to the Wiki How page <{wikihow_refresh}>`__

.. Special formatting
.. |br| raw:: html

   <br/>

""".format(**EXTERNAL_LINKS)

sphinx_tabs_valid_builders = ['linkcheck']

sphinx_tabs_disable_tab_closing = True

# Keep batch link checks bounded when third-party sites do not respond.
linkcheck_timeout = 10
linkcheck_workers = 20

# Redirects
rediraffe_redirects = "redirects.txt"
rediraffe_branch = "master"             # Main redirect branch
rediraffe_auto_redirect_perc = 100

templates_path = ['_templates']         # Templates path

# Source files
source_suffix = {
    '.rst': 'restructuredtext',
    '.md': 'markdown'
    }

source_encoding = 'utf-8-sig'

root_doc = 'index'

exclude_patterns = ['_build', 'README.md']      # Exclude files and directories from the build

nitpicky = True         # Warn about all references where the target cannot be found

# Project metadata
project = "Red Pitaya"
html_title = "Red Pitaya Documentation"
project_copyright = f"{datetime.date.today().year}, Red Pitaya d.o.o"
copyright = project_copyright
author = "Red Pitaya"

version = "3.00-57"
release = version

language = "zh_CN"

pygments_style = 'friendly'

# Build behavior
todo_include_todos = True

html_scaled_image_link = False
html_copy_source = True
html_show_sourcelink = False

numfig = True
numfig_format = {
    'figure': '图 %s',
    'table': '表 %s',
    'code-block': '代码清单 %s',
    'section': '第 %s 节',
}

suppress_warnings = [
    'image.nonlocal_uri',
    'ref.ref',
]

# HTML output
html_theme = 'sphinx_rtd_theme'

html_theme_options = {
    'logo_only': True,
    'collapse_navigation': False,
    'navigation_depth': 3,
    'includehidden': True,
    'titles_only': False,
    'sticky_navigation': True,
    'prev_next_buttons_location': 'bottom',
    'style_external_links': True,
    'vcs_pageview_mode': '',
    'analytics_id': '',
    'analytics_anonymize_ip': False,
}

html_static_path = ['_static']

html_logo = "img/redpitaya-logo.svg"

html_favicon = "img/favicon.png"

html_meta = {
    'description': 'Official Red Pitaya technical documentation',
    'keywords': 'Red Pitaya, FPGA, oscilloscope, signal generator, documentation',
    'author': 'Red Pitaya d.o.o',
    'viewport': 'width=device-width, initial-scale=1.0',
}

html_css_files = [
    'pygments.css',
    'page_width.css',
    'tabs.css',
    'new_style.css'
]

html_context = {
        'css_files': [
            'https://media.readthedocs.org/css/sphinx_rtd_theme.css',
            'https://media.readthedocs.org/css/readthedocs-doc-embed.css',
            '_static/pygments.css',
            '_static/page_width.css',
            '_static/tabs.css',
            '_static/new_style.css'
        ],
    }

htmlhelp_basename = 'RedPitayaDocs'

# MathJax configuration

mathjax3_config = {
    'loader': {'load': ['output/svg']},
    'startup': {'output': 'svg'},
}

# LaTeX output

latex_elements = {
}

latex_documents = [
    (root_doc, 'RedPitaya-Documentation.tex', html_title, author, 'manual'),
]

latex_logo = "img/head_logo.png"

# Manual pages

man_pages = [
    (root_doc, 'RedPitaya-Documetantion', html_title, author, 1)
]

# Texinfo output

texinfo_documents = [
    (root_doc, 'RedPitaya-Documentation', html_title, author, 'RedPitaya',
    'Red Pitaya Techincal Documentation', 'Miscellaneous'),
]

intersphinx_mapping = {
    'knowledgebase': ('https://redpitaya-knowledge-base.readthedocs.io/en/latest/', None),
    'python': ('https://docs.python.org/3/', None),
    'sphinx': ('https://www.sphinx-doc.org/en/master/', None),
}

intersphinx_disabled_reftypes = ["*"]

if on_rtd:
    html_theme_path = []
    html_baseurl = 'https://redpitaya.readthedocs.io/'
    html_theme_options.update({
        'analytics_id': '',
        'analytics_anonymize_ip': False,
        'logo_only': True,
        'prev_next_buttons_location': 'bottom',
        'style_external_links': False,
        'vcs_pageview_mode': '',
        'style_nav_header_background': 'white',
        'collapse_navigation': False,
        'sticky_navigation': True,
        'navigation_depth': 4,
        'includehidden': True,
        'titles_only': False
    })
else:
    html_theme_options.update({
        'collapse_navigation': False,
    })
