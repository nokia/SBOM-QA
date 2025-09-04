# SBOM_Quality-Assurance_Guide

## 1. Scope
The project covers:
- Open-source software repositories as test targets, including multiple programming languages and ecosystems.
- Generation and analysis of SBOMs in [SPDX](https://spdx.dev/specifications/) format.
- Use of reference SBOMs exported from original repository dependency graphs to serve as a consistent baseline.
- Alignment with the [OpenChain Telco SBOM Guide](https://www.openchainproject.org/standard/telco-sbom) to ensure standardized practices for SBOM structure, content, and validation.
- Evaluation of tool performance, accuracy, and coverage to inform reliable and actionable benchmarking results.

This project is licensed under the [BSD 3-Clause License](https://github.com/nokia/SBOM-QA/blob/main/LICENSE). 

## 2. Terms and Definition
### SBOM
A Software Bill of Materials (SBOM) is a structured inventory of all software components, libraries, and dependencies within an application, including key metadata such as version, license, and origin. It enhances transparency, security, and compliance across the software supply chain.
### SBOM Types
SBOMs can exist at different stages of the software lifecycle, including *Design, Source, Build, Analyzed, Deployed,* and *Runtime*, as defined in the [CISA guidelines](https://www.cisa.gov/sbom).
### Data Format
Data Format refers to the structure in which SBOM information is represented. Common formats include [SPDX](https://spdx.dev/), [CycloneDX](https://cyclonedx.org/), [SWID](https://www.iso.org/standard/65871.html), or other proprietary formats. For the purposes of this case study, the SBOM is represented using the **SPDX** format.
### Package 
A package is a reusable software unit, such as a library or module, distributed via package managers and accompanied by metadata including version, license, and authorship.
### Package Manager 
A package manager is a tool that automates the installation, upgrade, configuration, and removal of software packages, resolving both direct and transitive dependencies; examples include npm, pip, Maven, Gradle, and Conan.
### SCA Tools (Software Composition Analysis)
Tools that analyze software artifacts to identify components and extract metadata (e.g., licenses, versions, suppliers, vulnerabilities), commonly used to generate SBOMs for transparency, compliance, and security.
### Direct Dependency
A direct dependency is a first-level package or component explicitly declared in a project’s configuration or build file.
### Transitive Dependency
A transitive dependency is an indirect package required by a direct dependency of a project.


## 3. Methodology
### 3.1. Tools
#### 1. [Syft](https://github.com/anchore/syft) | [Docs](https://anchore.com/opensource/syft/)  
A CLI tool and Go library for generating an SBOM from container images and filesystems.  
Exceptional for SBOM creation and integrates well with vulnerability scanners like [Grype](https://github.com/anchore/grype).
#### 2. [Trivy](https://github.com/aquasecurity/trivy) | [Docs](https://aquasecurity.github.io/trivy/)  
A comprehensive security tool for SBOM generation, vulnerability detection, license analysis, misconfiguration scanning, and secret discovery across container images, filesystems, repositories, VMs, and Kubernetes environments.  
#### 3. [OSS Review Toolkit (ORT)](https://github.com/oss-review-toolkit/ort) | [Docs](https://oss-review-toolkit.org/)  
A policy automation and orchestration toolkit for SBOM generation, license compliance, vulnerability detection, and open-source risk management. ORT supports CycloneDX, SPDX, and custom attribution documents, while enabling policy-as-code checks, dependency analysis, and automated reporting across software projects.  
#### 4. [SCANOSS](https://github.com/scanoss/scanoss.py) | [Docs](https://osskb.org/docs)  
The SCANOSS Python package provides a simple library for interacting with SCANOSS APIs and engine, enabling SBOM generation, license compliance, and open-source component identification.  




## 3.2. Test Target
The test targets linked in this part are the original, publicly available repositories of the respective projects. 

### 1. [C++ (Conan)](https://github.com/catchorg/Catch2)  
[Catch2](https://github.com/catchorg/Catch2) is a modern, header-only testing framework for C++. It provides robust unit testing, micro-benchmarking, and test case management. For this study, the project is managed using the [Conan](https://conan.io/) package manager.

### 2. [Go](https://github.com/gohugoio/hugo)  
[Hugo](https://github.com/gohugoio/hugo) is a fast and flexible static site generator written in Go. It is widely used for websites, blogs, documentation, and portfolios.

### 3. [Node.js](https://github.com/expressjs/express)  
[Express](https://github.com/expressjs/express) is a minimal and flexible Node.js web application framework that provides robust features for building web and mobile applications.

### 4. [Java (Gradle-managed)](https://github.com/elastic/elasticsearch)  
[Elasticsearch](https://github.com/elastic/elasticsearch) is a distributed, RESTful search and analytics engine optimized for speed and relevance on production-scale workloads. It is managed using [Gradle](https://gradle.org/) package manager.

### 5. [Python (FastAPI)](https://github.com/fastapi/fastapi) | [Python (GPT Engineer)](https://github.com/AntonOsika/gpt-engineer)
- [FastAPI](https://github.com/fastapi/fastapi) is a modern, fast (high-performance) web framework for building APIs with Python 3.7+ based on standard Python type hints. It is widely used for developing web applications and APIs efficiently.

- [GPT Engineer](https://github.com/AntonOsika/gpt-engineer) is a Python project designed to facilitate building AI-driven solutions and applications, providing a structured environment for rapid prototyping and experimentation.

### 6. [Java (Maven-managed)](https://github.com/bytedeco/javacv)  
[JavaCV](https://github.com/bytedeco/javacv) is a Java interface to OpenCV, FFmpeg, and other computer vision and machine learning libraries. It provides a comprehensive set of tools for image and video processing, machine learning, and computer vision tasks. The project is managed using the [Maven](https://maven.apache.org/) package manager.

### 7. [C (No package manager)](https://github.com/besser82/libxcrypt)  
[libxcrypt](https://github.com/besser82/libxcrypt) is a modern library for one-way hashing of passwords, supporting various algorithms like bcrypt, md5crypt, and yescrypt. It provides traditional Unix `crypt` interfaces and extended functions for secure password handling. The project does not utilize a package manager, making it suitable for manual integration and analysis.

### 8. [C++ (No package manager)](https://github.com/zeux/meshoptimizer)  
[MeshOptimizer](https://github.com/zeux/meshoptimizer) is an open-source C++ library developed by Arseny Kapoulkine, providing algorithms to optimize meshes for modern GPU vertex and index processing pipelines. It can reindex an existing index buffer or generate an entirely new set of indices from an unindexed vertex buffer. The project does not utilize a package manager, making it suitable for manual integration and analysis.

### 9. [ContainerImage](https://github.com/pangenome/pggb)  
[pggb](https://github.com/pangenome/pggb) builds pangenome variation graphs from input sequences using wfmash, seqwish, smoothxg, gfaffix, and odgi.  

The project provides a **Dockerfile** for containerized usage, enabling local builds or pulls from the GitHub Container Registry.




**Note:** In the Observations section, the cloned copies and case study directories used for testing and SBOM generation are detailed, including the specific tags checked out.



## 3.3. Reference SBOM
A **Reference SBOM** is a standardized, machine-readable inventory of a project's dependencies and associated metadata, such as versions, licenses, and transitive relationships. It is generated directly from the **dependency graph** of the original, publicly available repositories of the respective test targets.

These SBOMs provide a canonical view of all software components, including direct and transitive dependencies, and serve as a baseline for comparison and validation. The dependency graph is a summary of the manifest and lock files stored in a repository and any dependencies that are submitted for the repository using the dependency submission API ([GitHub Docs: Dependency Graph](https://docs.github.com/en/code-security/supply-chain-security/understanding-your-software-supply-chain/about-the-dependency-graph?utm_source=chatgpt.com)).

For each test target, the Reference SBOM was exported from its **GitHub repository** using automated SBOM generation tools. These SBOMs capture the original dependency tree and associated metadata (e.g., versions, licenses) before any modifications or local testing. GitHub facilitates this process by allowing users to export an SBOM from a repository's dependency graph via the UI or REST API, producing an SPDX-compatible JSON file ([GitHub Docs: Exporting SBOM](https://docs.github.com/en/code-security/supply-chain-security/understanding-your-software-supply-chain/exporting-a-software-bill-of-materials-for-your-repository?utm_source=chatgpt.com)).



---

## Observation & Result

## Tools Used
### [Syft](https://github.com/anchore/syft)
**Command:**  
For generating SBOMs for all test targets this command is used:
```
syft -o spdx-json=syft-sbom.json --enrich all --verbose .
```

**Ecosystem:** [Node.js](https://github.com/nokia/SBOM-QA/tree/main/Node.js)


**Compilation Step:**
The project did not originally include a package-lock.json file, which is required to resolve and capture the full dependency tree. To generate it, the following command was executed in test target root:
```
npm install --package-lock
```
**Generated Files:**
package-lock.json , node_modules.

**Generated SBOMs:**
[Syft-lock-Node.js](https://github.com/nokia/SBOM-QA/blob/main/Node.js/SBOM/syft-lock-production.json) , [Syft-default-Node.js]


### [Scanoss](https://github.com/scanoss) 
**Command:**  

### [ORT](https://github.com/oss-review-toolkit/ort)  
**Command:**

### [Trivy](https://github.com/aquasecurity/trivy)  
**Command:** 

---

## Container-Based Tools

### Syft
- Version:  
- Command:  
- Notes / Observations:  

### Tern
- Version:  
- Command:   
- Notes / Observations:  

### Distro2sbom
- Version:  
- Command:   
- Notes / Observations:

---

## Conclusion

### Ecosystem Point of View
- Insights about ecosystem (e.g., package management).

### Tools Point of View
- Strengths and weaknesses of tools used.

### Quality Point of View
- Validation results  
- Diffs / comparisons

