# SBOM-QualityAssurance-Guide

## 1. Scope
- 

## 2. Terms and Definition
### SBOM
A Software Bill of Materials (SBOM) is a structured inventory of all software components, libraries, and dependencies within an application, including key metadata such as version, license, and origin. It enhances transparency, security, and compliance across the software supply chain.
### SBOM Types: 
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
### Tools
- List and describe tools used.

## 4. Test Target
- Define the targets for testing.

## 4. Reference SBOM
- Mention references and SBOM (Software Bill of Materials).


---

## Observation & Result

## Tools Used
### [Syft](https://github.com/anchore/syft)
**Command:**  
```
syft -o spdx-json=syft-sbom.json --enrich all --verbose
```

**Ecosystem:** [Node.js]()


Notes / Observations:

The project initially lacked a package-lock.json file, required to capture the full dependency tree.

Generated files: syft-sbom.json, package-lock.json, and node_modules.
  - Test Target:
  - Notes / Observations:

### Scanoss 
  - Command:  
  - Test Target:
  - Notes / Observations:

### ORT  
  - Command:  
  - Test Target:
  - Notes / Observations:

### Trivy  
  - Command:  
  - Test Target:
  - Notes / Observations:


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

