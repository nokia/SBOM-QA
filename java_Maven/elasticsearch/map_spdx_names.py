import json

# Load SPDX JSON data
with open('sbom.jason', 'r') as f:
    data = json.load(f)

# Step 1: Create map of SPDXID -> name
id_to_name = {}
for pkg in data.get("packages", []):
    spdx_id = pkg.get("SPDXID")
    name = pkg.get("name", "UNKNOWN")
    if spdx_id:
        id_to_name[spdx_id] = name

# Step 2: Translate relationships (if they exist)
relationships = data.get("relationships", [])

resolved_relationships = []
for rel in relationships:
    source_id = rel.get("spdxElementId")
    target_id = rel.get("relatedSpdxElement")
    relation_type = rel.get("relationshipType")

    resolved_relationships.append({
        "from": id_to_name.get(source_id, source_id),
        "to": id_to_name.get(target_id, target_id),
        "type": relation_type
    })

# Step 3: Save mapped relationships
with open('sbom_resolved.json', 'w') as f:
    json.dump(resolved_relationships, f, indent=2)

print("✅ Done! Saved readable relationships in sbom_resolved.json")

