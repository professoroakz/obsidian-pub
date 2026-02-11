# Legacy setup.py for backwards compatibility
from setuptools import setup, find_packages

setup(
    name="obsidian-pub",
    use_scm_version=True,
    setup_requires=["setuptools_scm"],
    packages=find_packages(),
    entry_points={
        "console_scripts": [
            "obsidian-pub=obsidian_pub.cli:main",
        ],
    },
)
