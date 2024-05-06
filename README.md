# IOT_Technology
 
# IOT_Jenkins_SErver

##  Tutorials overview

This part of the Jenkins User Documentation contains a series of introductory tutorials to help you begin building your applications in an automated fashion with Jenkins.
If you’re a developer who wants to improve your understanding of Continuous Integration (CI) / Continuous Delivery (CD) concepts, or you might already be familiar with these concepts but don’t yet know how to implement them in Jenkins, then these tutorials are a great place to start.


## User Handbook Overview

This page provides an overview of the documentation in the Jenkins User Handbook.

If you want to get up and running with Jenkins, see Installing Jenkins for procedures on how to install Jenkins on your supported platform of choice.

If you are a typical Jenkins user (of any skill level) who wants to know more about Jenkins usage, see Using Jenkins. Also refer to the separate Pipeline and Blue Ocean chapters for more information about these core Jenkins features.

If you are a Jenkins administrator and want to know more about managing Jenkins nodes and instances, see Managing Jenkins.

If you are a system administrator and want to learn how to back-up, restore, maintain as Jenkins servers and nodes, see Jenkins System Administration.


### Platform Information

This chapter provides information about the operating systems, web browsers, Java versions, and other software components commonly used to run Jenkins.

The content is suitable for users of all levels, especially those getting started with Jenkins.
Support policies

The Jenkins project defines support levels for platform components such as Java versions, operating systems, web browsers, and servlet containers. Support levels provide guidance on the effort Jenkins project contributors generally apply to issues related to platform components.

Details of the support policies are available in the specific support policy pages:

   - Java

   - Linux

  -  Windows

 -   Servlet containers

 -   Web browsers

#### Java support and upgrade information

In addition to support policies, this chapter provides information on upgrading your Java version in Jenkins. Depending on your current Java version, there are instructions for upgrading to Java 11 and upgrading to Java 17.

### Linux Support Policy

This page documents the Linux support policy for the Jenkins controller and agents.
Scope

Individual Jenkins plugins may set additional requirements for Linux versions on controllers and/or agents. This page does not document such requirements. Refer to plugin documentation for additional requirements.
Why?

Theoretically, Jenkins can run everywhere where you can run a supported Java version, but there are some limitations in practice. Jenkins core and some plugins include native code or depend on Linux API and subsystems, which make them dependent on specific Linux versions. Jenkins platform specific installation packages rely on specific Linux versions.
Support levels

We define multiple support levels for Linux platforms.


##  Linux

##### Jenkins installers are available for several Linux distributions.

  -  Debian/Ubuntu

   - Fedora

  -  Red Hat/Alma/Rocky

##### Prerequisites

- Minimum hardware requirements:

    - 256 MB of RAM

    - 1 GB of drive space (although 10 GB is a recommended minimum if running Jenkins as a Docker container)

##### Recommended hardware configuration for a small team:

  -   4 GB+ of RAM

  -   50 GB+ of drive space

##### Comprehensive hardware recommendations:

  -  Hardware: see the Hardware Recommendations page

##### Software requirements:

  -  Java: see the Java Requirements page

   - Web browser: see the Web Browser Compatibility page

  -  For Windows operating system: Windows Support Policy

  -  For Linux operating system: Linux Support Policy

   - For servlet containers: Servlet Container Support Policy

### Debian/Ubuntu

On Debian and Debian-based distributions like Ubuntu you can install Jenkins through apt.
	With the release of Debian 12, OpenJDK 11 is no longer included. It has been replaced with OpenJDK 17, which is reflected in the instructions below.
Long Term Support release


#### A LTS (Long-Term Support) release is chosen every 12 weeks from the stream of regular releases as the stable release for that time period. It can be installed from the debian-stable apt repository.

- sudo wget -O /usr/share/keyrings/jenkins-keyring.asc \
-   https://pkg.jenkins.io/debian-stable/jenkins.io-2023.key
- echo "deb [signed-by=/usr/share/keyrings/jenkins-keyring.asc]" \
   https://pkg.jenkins.io/debian-stable binary/ | sudo tee \
  /etc/apt/sources.list.d/jenkins.list > /dev/null
- sudo apt-get update
- sudo apt-get install jenkins

##### Weekly release

A new release is produced weekly to deliver bug fixes and features to users and plugin developers. It can be installed from the debian apt repository.

- sudo wget -O /usr/share/keyrings/jenkins-keyring.asc \
  https://pkg.jenkins.io/debian/jenkins.io-2023.key
- echo "deb [signed-by=/usr/share/keyrings/jenkins-keyring.asc]" \
  https://pkg.jenkins.io/debian binary/ | sudo tee \
  /etc/apt/sources.list.d/jenkins.list > /dev/null
- sudo apt-get update
- sudo apt-get install jenkins



Beginning with Jenkins 2.335 and Jenkins 2.332.1, the package is configured with systemd rather than the older System V init. See the DigitalOcean community systemd tutorial to better understand the benefits of systemd and the systemctl command.

The package installation will:

  -  Setup Jenkins as a daemon launched on start. Run systemctl cat jenkins for more details.

  -  Create a ‘jenkins’ user to run this service.

  -  Direct console log output to systemd-journald. Run journalctl -u jenkins.service if you are troubleshooting Jenkins.

  -  Populate /lib/systemd/system/jenkins.service with configuration parameters for the launch, e.g JENKINS_HOME

  -  Set Jenkins to listen on port 8080. Access this port with your browser to start configuration.

#### Installation of Java

Jenkins requires Java to run, yet not all Linux distributions include Java by default. Additionally, not all Java versions are compatible with Jenkins.

There are multiple Java implementations which you can use. OpenJDK is the most popular one at the moment, we will use it in this guide.

Update the Debian apt repositories, install OpenJDK 17, and check the installation with the commands:

- sudo apt update
- sudo apt install fontconfig openjdk-17-jre
- java -version
- openjdk version "17.0.8" 2023-07-18
- OpenJDK Runtime Environment (build 17.0.8+7-Debian-1deb12u1)
- OpenJDK 64-Bit Server VM (build 17.0.8+7-Debian-1deb12u1, mixed mode, sharing)

### Fedora

You can install Jenkins through dnf. You need to add the Jenkins repository from the Jenkins website to the package manager first.
Long Term Support release

A LTS (Long-Term Support) release is chosen every 12 weeks from the stream of regular releases as the stable release for that time period. It can be installed from the redhat-stable yum repository.

- sudo wget -O /etc/yum.repos.d/jenkins.repo \
    https://pkg.jenkins.io/redhat-stable/jenkins.repo
- sudo rpm --import https://pkg.jenkins.io/redhat-stable/jenkins.io-2023.key
- sudo dnf upgrade


##### Add required dependencies for the jenkins package
- sudo dnf install fontconfig java-17-openjdk
- sudo dnf install jenkins
- sudo systemctl daemon-reload

#### Weekly release

A new release is produced weekly to deliver bug fixes and features to users and plugin developers. It can be installed from the redhat yum repository.

- sudo wget -O /etc/yum.repos.d/jenkins.repo \
    https://pkg.jenkins.io/redhat/jenkins.repo
- sudo rpm --import https://pkg.jenkins.io/redhat/jenkins.io-2023.key
- sudo dnf upgrade
- 
###### Add required dependencies for the jenkins package
- sudo dnf install fontconfig java-17-openjdk
- sudo dnf install jenkins


### Start Jenkins

You can enable the Jenkins service to start at boot with the command:

- sudo systemctl enable jenkins

You can start the Jenkins service with the command:

- sudo systemctl start jenkins

You can check the status of the Jenkins service using the command:

- sudo systemctl status jenkins

If everything has been set up correctly, you should see an output like this:

Loaded: loaded (/lib/systemd/system/jenkins.service; enabled; vendor preset: enabled)
Active: active (running) since Tue 2018-11-13 16:19:01 +03; 4min 57s ago

###### If you have a firewall installed, you must add Jenkins as an exception. You must change YOURPORT in the script below to the port you want to use. Port 8080 is the most common.

- YOURPORT=8080
- PERM="--permanent"
- SERV="$PERM --service=jenkins"

- firewall-cmd $PERM --new-service=jenkins
- firewall-cmd $SERV --set-short="Jenkins ports"
- firewall-cmd $SERV --set-description="Jenkins port exceptions"
- firewall-cmd $SERV --add-port=$YOURPORT/tcp
- firewall-cmd $PERM --add-service=jenkins
- firewall-cmd --zone=public --add-service=http --permanent
- firewall-cmd --reload


###Red Hat/Alma/Rocky
You can install Jenkins through yum on Red Hat Enterprise Linux, Alma Linux, Rocky Linux, Oracle Linux, and other Red Hat based distributions.


#### Long Term Support release
A LTS (Long-Term Support) release is chosen every 12 weeks from the stream of regular releases as the stable release for that time period. It can be installed from the redhat-stable yum repository.

- sudo wget -O /etc/yum.repos.d/jenkins.repo \
    https://pkg.jenkins.io/redhat-stable/jenkins.repo
- sudo rpm --import https://pkg.jenkins.io/redhat-stable/jenkins.io-2023.key
- sudo yum upgrade
# Add required dependencies for the jenkins package
- sudo yum install fontconfig java-17-openjdk
- sudo yum install jenkins
- sudo systemctl daemon-reload


#### Weekly release
A new release is produced weekly to deliver bug fixes and features to users and plugin developers. It can be installed from the redhat yum repository.

- sudo wget -O /etc/yum.repos.d/jenkins.repo \
    https://pkg.jenkins.io/redhat/jenkins.repo
- sudo rpm --import https://pkg.jenkins.io/redhat/jenkins.io-2023.key
- sudo yum upgrade

####$ Add required dependencies for the jenkins package
- sudo yum install fontconfig java-17-openjdk
- sudo yum install jenkins

#### Start Jenkins
You can enable the Jenkins service to start at boot with the command:

- sudo systemctl enable jenkins
You can start the Jenkins service with the command:

- sudo systemctl start jenkins
You can check the status of the Jenkins service using the command:

- sudo systemctl status jenkins
If everything has been set up correctly, you should see an output like this:

Loaded: loaded (/lib/systemd/system/jenkins.service; enabled; vendor preset: enabled)
Active: active (running) since Tue 2023-06-22 16:19:01 +03; 4min 57s ago
...


If you have a firewall installed, you must add Jenkins as an exception. You must change YOURPORT in the script below to the port you want to use. Port 8080 is the most common.

- YOURPORT=8080
- PERM="--permanent"
- SERV="$PERM --service=jenkins"

- firewall-cmd $PERM --new-service=jenkins
- firewall-cmd $SERV --set-short="Jenkins ports"
- firewall-cmd $SERV --set-description="Jenkins port exceptions"
- firewall-cmd $SERV --add-port=$YOURPORT/tcp
- firewall-cmd $PERM --add-service=jenkins
- firewall-cmd --zone=public --add-service=http --permanent
- firewall-cmd --reload


##  Getting started with the Guided Tour

This guided tour introduces you to the basics of using Jenkins and its main feature, Jenkins Pipeline. This tour uses the "standalone" Jenkins distribution, which runs locally on your own machine.
Prerequisites

- For this tour, you will require:

    A machine with:

        256 MB of RAM, although more than 2 GB is recommended

        10 GB of drive space (for Jenkins and your Docker image)

    - The following software installed:

        Java 11, 17, or 21

        Docker (navigate to Get Docker site to access the Docker download that’s suitable for your platform)

## Download and run Jenkins

    Download Jenkins Generic Java package (.war)

    Open up a terminal in the download directory

    Run java -jar jenkins.war --httpPort=8080

    Browse to http://localhost:8080

    Follow the instructions to complete the installation

- When the installation is complete, you can start putting Jenkins to work!


## Creating your first Pipeline
### What is a Jenkins Pipeline?

enkins Pipeline (or simply "Pipeline") is a suite of plugins which supports implementing and integrating continuous delivery pipelines into Jenkins.

A continuous delivery pipeline is an automated expression of your process for getting software from version control right through to your users and customers.

Jenkins Pipeline provides an extensible set of tools for modeling simple-to-complex delivery pipelines "as code". The definition of a Jenkins Pipeline is typically written into a text file (called a Jenkinsfile) which in turn is checked into a project’s source control repository. [1]

For more information about Pipeline and what a Jenkinsfile is, refer to the respective Pipeline and Using a Jenkinsfile sections of the User Handbook.

### To get started quickly with Pipeline:

   -  Install the Docker Pipeline plugin through the Manage Jenkins > Plugins page

  -   After installing the plugin, restart Jenkins so that the plugin is ready to use

   -  Copy one of the examples below into your repository and name it Jenkinsfile
  
   -  Provide a name for your new item (e.g. My-Pipeline) and select Multibranch Pipeline

   - Click the Add Source button, choose the type of repository you want to use and fill in the details

    - Click the Save button and watch your first Pipeline run

You may need to modify one of the example Jenkinsfile's to make it run with your project. Try modifying the sh command to run the same command you would run on your local machine.

After you have setup your Pipeline, Jenkins will automatically detect any new Branches or Pull Requests that are created in your repository and start running Pipelines for them.



## Quick Start Examples

Below are some easily copied and pasted examples of a simple Pipeline with various languages.

#### Java
Jenkinsfile (Declarative Pipeline)

/* Requires the Docker Pipeline plugin */
pipeline {
    agent { docker { image 'maven:3.9.6-eclipse-temurin-17-alpine' } }
    stages {
        stage('build') {
            steps {
                sh 'mvn --version'
            }
        }
    }
}


#### Python
Jenkinsfile (Declarative Pipeline)

/* Requires the Docker Pipeline plugin */
pipeline {
    agent { docker { image 'python:3.12.1-alpine3.19' } }
    stages {
        stage('build') {
            steps {
                sh 'python --version'
            }
        }
    }
}

#### Go
Jenkinsfile (Declarative Pipeline)

/* Requires the Docker Pipeline plugin */
pipeline {
    agent { docker { image 'golang:1.22.2-alpine3.19' } }
    stages {
        stage('build') {
            steps {
                sh 'go version'
            }
        }
    }
}


## Running multiple steps

Pipelines are made up of multiple steps that allow you to build, test and deploy applications. Jenkins Pipeline allows you to compose multiple steps in an easy way that can help you model any sort of automation process.

Think of a "step" like a single command which performs a single action. When a step succeeds it moves onto the next step. When a step fails to execute correctly the Pipeline will fail.

When all the steps in the Pipeline have successfully completed, the Pipeline is considered to have successfully executed.

### Linux, BSD, and Mac OS

On Linux, BSD, and Mac OS (Unix-like) systems, the sh step is used to execute a shell command in a Pipeline.
Jenkinsfile (Declarative Pipeline)

pipeline {
    agent any
    stages {
        stage('Build') {
            steps {
                sh 'echo "Hello World"'
                sh '''
                    echo "Multiline shell steps works too"
                    ls -lah
                '''
            }
        }
    }
}


### Windows

Windows-based systems should use the bat step for executing batch commands.
Jenkinsfile (Declarative Pipeline)

pipeline {
    agent any
    stages {
        stage('Build') {
            steps {
                bat 'set'
            }
        }
    }
}


## Timeouts, retries and more

There are some powerful steps that "wrap" other steps which can easily solve problems like retrying (retry) steps until successful or exiting if a step takes too long (timeout).

When a step cannot be completed, timeouts help the controller avoid wasting resources. This video reviews the process of setting up both stage and global timeouts.




## Managing Jenkins


Most standard administrative tasks can be performed from the screens in the Manage Jenkins section of the dashboard. In this chapter, we look at these screens and explain how to use them.

The tiles displayed on the Manage Jenkins page are grouped logically. Here we discuss the pages that are part of the standard installation. Plugins may add pages to this screen.

The top of the Manage Jenkins screen may contain "Monitors" that alert you when a new version of the Jenkins software or a security update is available. Each monitor includes a description of the issue it is reporting and links to additional information about the issue

Inline help is available on most Manage Jenkins pages:

   - To access the help, select the ? icon to the right of each field.

   - Click the ? icon again to hide the help text.

Other system administration topics are discussed in Jenkins System Administration.

#### System Configuration group

Screens for configuring resources for your Jenkins instance.

##### System

    Configure global settings and paths for the Jenkins instance
##### Tools

    Configure tools, their locations, and automatic installers
##### Plugins

    Add, update, remove, disable/enable plugins that extend the functionality of Jenkins.
##### Nodes and Clouds

    Add, remove, control, and monitor the nodes used for the agents on which build jobs run.
##### Configuration as Code

    Configure your Jenkins instance using a human-readable YAML file rather than the UI. This is an optional feature that appears in this group only when the plugin is installed on your controller.

#### Security group

Screens for configuring security features for your Jenkins instance. See Securing Jenkins for general information about managing Jenkins security.

##### Security

    Set configuration parameters that secure your Jenkins instance.
##### Manage Credentials

    Configure the credentials that provide secure access to third-party sites and applications that interact with Jenkins.
##### Credential Providers

    Configure credential providers and types
##### Users

    Manage users defined in the Jenkins user database. This is not used if you use a different security realm such as LDAP or AD.

#### Status Information group

##### System Information

    Displays information about the Jenkins environment.
##### System Log

    Jenkins log that contains all java.util.logging output related to Jenkins.
##### Load Statistics

    Displays information about resource utilization on you Jenkins instance.
##### About Jenkins

    Provides version and license information for your Jenkins instance.

#### Troubleshooting group

##### Manage Old Data

    Remove configuration information related to plugins that have been removed from the instance.

##### Tools and Actions group

Screens for common management tasks and management tools that enable you to do administrative tasks without using the UI.

##### Reload Configuration from Disk

    Discard all data that is loaded in memory and reload everything from the file system. This is useful when you modify configuration files directly on disk.
##### Jenkins CLI

    How to use the Jenkins CLI from a shell or script.
##### Script Console

    Execute an Apache Groovy script for administration, troubleshooting, and diagnostics.
Prepare for Shutdown

    Prevents new builds from starting so that the system can be shut down safely. Displays a red banner with a custom message so that users know what is about to happen.


