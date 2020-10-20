import overpy
api = overpy.Overpass()
result = api.query("""node["name"="Нижневартовск"];out body;""")
print(result.nodes)