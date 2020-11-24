import setuptools

with open("README.md", "r") as fh:
    long_description = fh.read()

setuptools.setup(
    name="enpix", 
    version="1.0.4",
    author="Nishant Hada",
    author_email="hadanis.singh@gmail.com",
    description="Strongest Image Encryption",
    long_description="Image Encryption Algorithm based on Fisher-Yates Shuffling Algorithm and SHA256 Encryption.",
    long_description_content_type="text/markdown",
    url="https://github.com/ThisIsNSH/Enpix/Python",
    packages=setuptools.find_packages(),
    classifiers=[
        "Programming Language :: Python :: 3",
        "License :: OSI Approved :: MIT License",
        "Operating System :: OS Independent",
    ],
    python_requires='>=3.6',
)