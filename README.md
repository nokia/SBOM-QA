#  SBOM Quality Assurance (SBOM QA)

Welcome to **SBOM QA** — a benchmarking initiative for evaluating open source Software Composition Analysis (SCA) tools and their SBOM (Software Bill of Materials) outputs.

This project helps answer key questions:

-  *How complete is the SBOM?* Are all dependencies detected? Any false positives?
-  *What is the quality of the SBOM?* Is it compliant with the [OpenChain Telco SBOM Guide](https://openchainproject.org/news/2025/05/22/case-study-bytedance-telco)?

---

##  Work Methodology

1. **Test Targets** – Software artifacts with known dependencies built using various tech stacks.
2. **Reference SBOMs** – Exporting SBOM via GitHub Dependencies Graph of Origin Projects.
3. **SCA Tools** – Open source tools selected for analysis.
4. **Benchmarking** – We compare tool-generated SBOMs with reference SBOMs and document results.

---

##  Test Targets

| ID | Description                        | Tag                    | Artefact                     | Reference SBOM                              | Original Repo |
|----|------------------------------------|------------------------|------------------------------|---------------------------------------------|---------|
| 1  | C++ without package manager        | `v38.0.0-nightly.20250521` | [C++/electron](C++/electron) | [C++/electron_electron_dcefc2.json](C++/electron_electron_dcefc2.json) | https://github.com/electron/electron
| 2  | C without package manager          | `v7_0_2beta`           |  [C/curl](C/curl) | [C/curl_curl_0c7fe9.json](C/curl_curl_0c7fe9.json) | https://github.com/curl/curl
| 3  | C++ with Conan                     | `v1.0.0`               | [C++_CONAN/Coronan](C++_CONAN/Coronan) | [C++_CONAN/bbvch_Coronan_81a3f3.json](C++_CONAN/bbvch_Coronan_81a3f3.json)  | https://github.com/bbvch/Coronan
| 4  | Go with dependencies               | `v0.147.4`             | [Go/hugo](Go/hugo) | [Go/gohugoio_hugo_b0888a.json](Go/gohugoio_hugo_b0888a.json)  | https://github.com/gohugoio/hugo
| 5  | Python with dependencies           | `0.116.1`              | [python/fastapi](python/fastapi) | [python/fastapi_fastapi_1aca71.json](python/fastapi_fastapi_1aca71.json) | https://github.com/fastapi/fastapi
| 6  | Node.js (npm)                      | `v5.1.0`               | [Node.js/express](Node.js/express) | [Node.js/expressjs_express_98d8b1.json](Node.js/expressjs_express_98d8b1.json) | https://github.com/expressjs/express
| 7  | Java with gradle                  | `v9.0.1`               | [java/elasticsearch](java/elasticsearch) | [java/elastic_elasticsearch_3c796f.json](java/elastic_elasticsearch_3c796f.json) | https://github.com/elastic/elasticsearch
| 8  | Container image with mixed installs| `v0.7.4`               | [ContainerImage/pggb](ContainerImage/pggb) | [ContainerImage/pangenome_pggb_4e1835.json](ContainerImage/pangenome_pggb_4e1835.json) | https://github.com/pangenome/pggb

---
##  New Test Targets

| ID | Description                        | Tag                    | Artefact                     | Reference SBOM                              | Original Repo |
|----|------------------------------------|------------------------|------------------------------|---------------------------------------------|---------|
| 1  | Python with requirements.txt       | `v0.3.1`              | [python/gpt-engineer](python/gpt-engineer) | [python/gpt_engineer_0f3e4b.json](python/gpt_engineer_0f3e4b.json) | https://github.com/AntonOsika/gpt-engineer |
| 2  | Java with Maven                     | `1.5.12`              | [java_Maven/bytedeco-javacv](java/bytedeco-javacv) | [java/bytedeco_javacv_1aa2ee.json](java_Maven/bytedeco_javacv_1aa2ee.json) | https://github.com/bytedeco/javacv |
| 3  | C without package manager          | `v1.9.1`           |  [C/libgit2](C/libgit2) | [C/libgit2_libgit2_92b6d7.json](C/libgit2_libgit2_92b6d7.json) | https://github.com/libgit2/libgit2

##  Open Source SCA Tools Used

| Tool              | Version    | Analysis Strategy                           | SPDX Support | Ecosystem Support                               | GitHub | Docs | CISA SBOM Types |
|------------------|------------ |---------------------------------------------|--------------|--------------------------------------------------|--------------------------- | -------------------------|--------------------------|
| **Syft**          |        |Package managers, file system metadata      | ✅ Yes       | Go, Java, Python, JS, C/C++, containers          | [anchore/syft](https://github.com/anchore/syft) | [Syft Docs](https://anchore.com/docs/syft/) | Source, Build, Analyze | 
| **ammend/syft**   |           | Syft fork with Telco SBOM Guide alignment   | ✅ Yes       | Same as Syft                                     | [ammend/syft](https://github.com/elhamrasti/syft) |           | Source, Build, Analyze |
| **Trivy**         |           | Filesystem & vulnerability analysis, SBOM Scaning        | ✅ Yes       | Containers, VMs, source code                     |   [aquasecurity/trivy](https://github.com/aquasecurity/trivy) | [Trivy Docs](https://aquasecurity.github.io/trivy/)  | Source, Build, Analyze, Deploy |
| **ORT**           |        | Source code, VCS, metadata                  | ✅ Yes       | Repositories                                     |  [oss-review-toolkit/ort](https://github.com/oss-review-toolkit/ort) | [ORT Docs](https://github.com/oss-review-toolkit/ort#documentation)  | Source, Build, Analyze |
| **SCANOSS**       |            | Code fingerprinting, snippet detection      | ✅ Yes       | All languages, AI-generated code | [scanoss/sbom-workbench](https://github.com/scanoss/sbom-workbench)     [scanoss](https://www.scanoss.com) | [scanoss Docs](https://github.com/scanoss/sbom-workbench) | Source |

**Note:** Assess SCANOSS output with and without API key access to understand the added value of the commercial dataset.

---

##  Container-Specific SBOM Tools

| Tool              | Version      | Analysis Strategy                  | SPDX Support | Ecosystem        |  GitHub | Docs | CISA SBOM Types |
|------------------|---------------- | -------------------------------------|--------------|------------------|---------------------------- | ----------------------------|--------------------|
| **Tern**          |            | Filesystem + Docker introspection  | ✅ Yes       | Linux containers | [tern-tools/tern](https://github.com/tern-tools/tern) | [Tern Docs](https://github.com/tern-tools/tern/tree/main/docs) | Build, Analyze    |
| **distro2sbom**   |        | Package metadata + TUF             | ✅ Yes   | Linux distros    | [theupdateframework/distro2sbom](https://github.com/anthonyharrison/distro2SBOM) | [distro2sbom Docs](https://github.com/anthonyharrison/distro2SBOM/blob/main/README.md) | Analyze |
| **Syft**          |         | Package managers, file system metadata, container images | ✅ Yes       | Go, Java, Python, JS, C/C++, containers          | [anchore/syft](https://github.com/anchore/syft) | [Syft Docs](https://anchore.com/docs/syft/) | Source, Build, Analyze | 


**Note:** [Syft](https://github.com/anchore/syft) supports scanning of **container images** (e.g., Docker, OCI) in addition to local file systems and source directories. It detects packages from image layers, which makes it useful for SBOM generation in container-based environments.


---
## Evaluation Criteria

-  **SBOM completeness**: Are all components found?
-  **Metadata correctness**: name, version, license, supplier, URL, hashes
-  **License detection**: Accuracy using SCANOSS dataset
-  **Format compatibility**: SPDX compliance, JSON validation
-  **Comparison** with:
  - Other SCA tools
  - Reference SBOMs
  - SCANOSS with/without commercial API

---

##  Project Structure

Each folder corresponds to a test case categorized by language, platform, or build system:

- **C/** → C projects without a package manager (e.g., `curl`, `libgit2`)
- **C++/** → C++ projects without a package manager (e.g., `electron`)
- **C++_CONAN/** → C++ projects using the Conan package manager
- **Go/** → Go modules projects (e.g., `hugo`)
- **Node.js/** → JavaScript projects using npm (e.g., `express`)
- **java_Maven/** → Java projects using Maven (e.g., `bytedeco-javacv`)
- **java_Gradle/** → Java projects using Gradle (e.g., `elasticsearch`)
- **python/** → Python projects with `requirements.txt` or `pipenv` (e.g., `fastapi`, `gpt-engineer`)
- **ContainerImage/** → Complex container setups with mixed install methods (e.g., `pggb`)

Each test folder contains:
- Source material or container image
- Reference SBOM 
- SBOMs from each SCA tool
- Metadata extraction and comparison output
- Tool version info
---

##  SBOM Generation Tools

- **Syft** – Primary SBOM generator used across test targets.
- **[ammend/syft](https://github.com/ammend/syft)** – A fork of Syft that, in theory, generates SPDX JSON compliant with the [OpenChain Telco SBOM Guide](https://openchainproject.org/news/2025/05/22/case-study-bytedance-telco). Ideal for telecom sector requirements.

---



