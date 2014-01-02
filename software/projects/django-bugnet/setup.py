#!/usr/bin/env python

import os
from glob import glob

if os.environ.get('USE_SETUPTOOLS'):
  from setuptools import setup
  setup_kwargs = dict(zip_safe=0)

else:
  from distutils.core import setup
  setup_kwargs = dict()


webapp_content = {}

for root, dirs, files in os.walk('webapp/content'):
  for filename in files:
    filepath = os.path.join(root, filename)

    if root not in webapp_content:
      webapp_content[root] = []

    webapp_content[root].append(filepath)


conf_files = [ ('conf', glob('conf/*.example')) ]
examples = [ ('examples', glob('examples/example-*')) ]

setup(
  name='django-bugnet',
  version=__import__('bugnet').get_version().replace(' ', '-'),
  url='http://dwb.ilhost.fr/',
  author='Nicolas DUPEUX',
  author_email='nicolas@dupeux.net',
  license='GPL2+',
  description=u' '.join(__import__('bugnet').__doc__.splitlines()).strip(),
  package_dir={'bugnet' : 'bugnet', 'graphite' : 'graphite' },
  packages=[
    'bugnet',
    'bugnet.jobs',
    'graphite',
  ],
  package_data={'graphite' :
    ['templates/admin/*', 'templates/*.html', 'local_settings.py.example']},
  scripts=glob('bin/*'),
  data_files=webapp_content.items() + conf_files + examples,
  **setup_kwargs
)
