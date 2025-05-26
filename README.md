# SBOM QA

Testing the quality of Software Compositon Analyzis (SCA) or SBOM generator tools. SCA tools are detecting the transient
dependencies of software. The purpose of this repository is to benchmark a handfull of open souce SCA tools and check

* How complete SBOM they generate. Are all the dependencies discovered and if there are any false positives?
* What is the quality of the generated SBOM. Is the SBOM compliant with the
[OpenChain Telco SBOM Guide](https://github.com/OpenChain-Project/Telco-WG/)?

## Work method

1. We select test targets. These are software artefacts created using different technologies with a know list of
   dependencies. We create reference SBOMs for the artefacts.
2. We select SCA tools. Due to the nature of the activity we use open source SCA tools, but the methodolgy can be
   applied to any SCA tool.
3. We run the SCA tools on the test targets and compare the result to the reference SBOMs. Results are documented.

### 1. Test targets


| id | Description | Tag | Artefact | Reference SBOM |
| -- | ----------- | --- | -------- | -------------- | 
| 1  | C++ code without package manager | v38.0.0-nightly.20250521 | [C++/electron](C++/electron) | [C++/electron_electron_dcefc2.json](C++/electron_electron_dcefc2.json) |
| 2  | C code without package manager | v7_0_2beta | [C/curl](C/curl) | [C/curl_curl_0c7fe9.json](C/curl_curl_0c7fe9.json) |
| 3  | C++ code with Conan package manager | v1.0.0 | [C++_CONAN/Coronan](C++_CONAN/Coronan) | [C++_CONAN/bbvch_Coronan_81a3f3.json](C++_CONAN/bbvch_Coronan_81a3f3.json) |
| 4  | Go module with dependencies | v0.147.4| [Go/hugo](Go/hugo) | [Go/gohugoio_hugo_b0888a.json](Go/gohugoio_hugo_b0888a.json) |
| 5  | Python module with dependencies | v0.1.16 | [python/fastapi](python/fastapi) | [python/fastapi_fastapi_1aca71.json](python/fastapi_fastapi_1aca71.json) |
| 6  | npm project with dependencies | v5.1.0 | [Node.js/express](Node.js/express) | [Node.js/expressjs_express_98d8b1.json](Node.js/expressjs_express_98d8b1.json) |
| 7  | Java project with Maven | v9.0.1 | [java_Maven/elasticsearch](java_Maven/elasticsearch) | [java_Maven/elastic_elasticsearch_3c796f.json](java_Maven/elastic_elasticsearch_3c796f.json) |
| 8  | Container image with apt-install, go install, wget, git clone and local copy of a zip file | v0.7.4 |  [ContainerImage/pggb](ContainerImage/pggb) | [ContainerImage/pangenome_pggb_4e1835.json](ContainerImage/pangenome_pggb_4e1835.json) |

### 2. Selected SCA tools

| Tool | Nontes |
| ---- | ------ |


# Folder Descriptions

Descriptions of each test folder and what it contains.

## C++ Projects
This folder contains C++ projects that are built without using a package manager. They typically use custom build systems or plain CMake.

**1. electron** – An open-source game engine for Windows and Linux. Not to be confused with GitHub's Electron framework, this project provides a complex, full-scale C++ codebase for a game engine with manual dependency handling.

## C++ with Conan Package Manager
The C++_CONAN folder includes C++ projects that explicitly use the Conan package manager to manage dependencies.

**1. Coronan** – A simple CMake-based C++ project that uses Conan to fetch and integrate common libraries like zlib or gtest. It serves as an example for integrating Conan with modern C++ projects.

## C Projects (No Package Manager)
The C folder contains well-known open-source C projects, built and configured manually without dependency managers like vcpkg or Conan.

**1. curl** – A powerful command-line tool and library (libcurl) for transferring data using various protocols including HTTP, FTP, and SMTP. It's known for its portable C codebase and rich feature set.

## Container Images
The ContainerImage folder contains folders or Dockerfiles used to build container images. These images may install software using a combination of package managers, custom binaries, and manual setups.

**1. pggb** – A bioinformatics pipeline for constructing pangenome graphs. It integrates several tools like seqwish, smoothxg, and others. The software is distributed as a container for easier reproducibility and execution in bioinformatics workflows.

## Go Projects
The Go folder contains projects written in the Go programming language, typically using Go modules for dependency management.

**1. hugo** – A fast, modern static site generator written in Go. It converts markdown files into complete HTML websites and is widely used in the developer and open-source communities.

## Node.js 
folder includes projects built using the Node.js runtime, often managed with npm or yarn.

**1. express** - A minimal and flexible web application framework for Node.js. It provides a thin layer of fundamental web features and is widely used to create server-side applications and REST APIs.

## Java Maven Projects
The java_Maven folder contains Java projects that use the Maven build system for compilation and dependency resolution.

**1. elasticsearch** - A distributed, scalable, real-time search and analytics engine built in Java. It's used to index and query large volumes of data and serves as the core engine behind the Elastic Stack.

## Python Projects
The Python folder contains software projects written in Python, using tools like pip or poetry for environment and dependency management.

**1. fastapi** - A modern Python web framework designed for building APIs quickly with automatic OpenAPI and JSON Schema generation. It’s built on top of Starlette and Pydantic and supports asynchronous programming.


# Software Composition Analysis (SCA) Tools & Container-Specific SBOM Tools

This document presents a curated list of open source tools for generating and analyzing Software Bill of Materials (SBOMs). The tools are grouped into two categories:

- **General SCA tools**: Work across multiple ecosystems.
- **Container-specific tools**: Focused on container images and environments.

Each tool is compared based on:
- **Analysis Strategy**: How the tool identifies dependencies (e.g., package manager data, binary analysis).
- **SPDX Support**: Whether the tool can output SPDX-compliant SBOMs.
- **Ecosystem Coverage**: Languages, runtimes, or targets supported.
- **Key Features**: Highlights of each tool.

---

## General-Purpose SCA Tools

| Tool | Analysis Strategy | SPDX Support | Ecosystem Coverage | Key Features | GitHub | Docs |
|------|-------------------|--------------|---------------------|--------------|--------|------|
| **Syft** | Package manager, file system metadata | ✅ Yes | Go, Java, Python, Ruby, JavaScript, C/C++, containers | SBOM generation (SPDX, CycloneDX), Docker/OCI support, CLI/API | [anchore/syft](https://github.com/anchore/syft) | [Syft Docs](https://anchore.com/docs/syft/) |
| **Tern** | File system inspection, Docker introspection | ✅ Yes | Linux containers | SBOM creation from container layers, SPDX support, Python-based | [tern-tools/tern](https://github.com/tern-tools/tern) | [Tern Docs](https://github.com/tern-tools/tern/blob/main/docs/index.md) |
| **SPDX Generator** | Package metadata from managers | ✅ Yes | Python, Java, JS, C/C++ | Generates SPDX 2.2+, supported by SPDX working group | [spdx/spdx-sbom-generator](https://github.com/spdx/spdx-sbom-generator) | [SPDX Generator Docs](https://github.com/spdx/spdx-sbom-generator#usage) |
| **SBOM-rs** | File system + metadata parsing | ✅ Yes | Rust, Linux, containers | Lightweight, Rust-based SBOM tool, SPDX and CycloneDX output | [authzed/sbom-rs](https://github.com/authzed/sbom-rs) | [SBOM-rs Docs](https://github.com/authzed/sbom-rs#usage) |
| **ScanCode Toolkit** | Source code & license scanning | ✅ Yes | Python, Java, JS, C/C++, Ruby, etc. | Deep license + dependency scan, SPDX generation | [nexB/scancode-toolkit](https://github.com/nexB/scancode-toolkit) | [ScanCode Docs](https://scancode-toolkit.readthedocs.io/) |

---

## Container-Specific SBOM Tools

| Tool | Analysis Strategy | SPDX Support | Ecosystem | Key Features | GitHub | Docs |
|------|-------------------|--------------|------------|--------------|--------|------|
| **Trivy** | Package manager, filesystem, vulnerabilities | ✅ Yes | Containers, VMs, source code | Vulnerability scanning, SBOM output (SPDX, CycloneDX), license scan | [aquasecurity/trivy](https://github.com/aquasecurity/trivy) | [Trivy Docs](https://aquasecurity.github.io/trivy/) |
| **Docker SBOM** | Docker CLI plugin (experimental) | ✅ Yes | Docker images | Native Docker SBOM tool (JSON, SPDX), simple integration | [moby/buildkit (sbom)](https://github.com/moby/buildkit) | [Docker SBOM Docs](https://docs.docker.com/go/sbom/) |
| **CNSpec** | Policy-as-code, config + SBOM inspection | ⚠️ Partial | Containers, cloud infra | Compliance rules, checks SBOMs, not full generator | [mundialis/cnspec](https://github.com/mondoo/cnspec) | [CNSpec Docs](https://mondoo.com/docs/cnspec/) |
| **Grype** | Layer, package metadata, binaries | ✅ Yes | Containers (OCI, Docker), Linux | CVE scanning, pairs with Syft, supports SP

