# How to Install GCC Compiler on Ubuntu 22.04

# Medium 1: Installing GCC Compiler from Ubuntu Repositories in this Method.

The apt package manager is the quickest way to install GCC on Ubuntu. Nevertheless. There are drawbacks to installing GCC from the Ubuntu repositories, including a lack of customization options and potential dependency conflicts.

GCC compiler installation through Ubuntu repository:


# 3 Step 1: Update Package Repository

Use the command below to update the Ubuntu package repository:
>> sudo apt update


## Step 2. Install build-essential Package

Install the package known as build-essential:
>> sudo apt install build-essential


## Step 3: Determine GCC Version

To determine the GCC version, use the command:
>> gcc --version

command to check gcc version

# Medium 2: Installing several GCC Versions on Ubuntu using this Method

Users can install a certain GCC version (or multiple GCC versions) quickly and easily by using GCC PPAs (Personal Package Archives).

To do this:

## Step 1: Update Repository First

Update the repository for Ubuntu packages:
>> sudo apt update
>>

## Step 2: Install Software-Properties Common Package

Execute the following command to install the software-properties-common package:
>> sudo apt install software-properties-common



## Step 3: In the Below Step Include the GCC PPA

Include the GCC PPA, which contains every GCC compiler version:
>> sudo add-apt-repository ppa:ubuntu-toolchain-r/test

command sudo add apt repository

## Step 4: Now, Add the PPA Packages

Add the PPA packages to the updated package list:
>> sudo apt update


## Step 5: The next thing is to Install One or More GCC Versions

Use the command listed below to install one or more GCC versions. For instance, type: to install GCC 12 and GCC 13.
>> sudo apt install gcc-12 g++-12 gcc-13 g++-13 -y

command to install specific version or multiple versions of gcc

## Step 6: Solution to Handle Several GCC Versions

Users can handle several GCC versions with the update-alternatives tool: The update-alternatives filesystem should now include the GCC 12 alternative.
>> sudo update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-12 12 --slave /usr/bin/g++ g++ /usr/bin/g++-12



The update-alternatives filesystem should now include the GCC 13 alternative.
>> sudo update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-13 13 --slave /usr/bin/g++ g++ /usr/bin/g++-13


##  Step 7: Switch Between Installed GCC Versions

To switch between the installed GCC versions, use the update-alternatives tool:
>> sudo update-alternatives --config gcc

here are 2 choices for the alternative gcc (providing /usr/bin/gcc).

  Selection    Path             Priority   Status
------------------------------------------------------------
* 0            /usr/bin/gcc-13   13        auto mode
  1            /usr/bin/gcc-12   12        manual mode
  2            /usr/bin/gcc-13   13        manual mode

Press <enter> to keep the current choice[*], or type selection number: 




## Step 8: Determine the Most Recent GCC Version

Use the following command to determine the most recent GCC version:
>> gcc --version

