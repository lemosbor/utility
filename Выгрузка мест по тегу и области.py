import overpy
import json # модуль для работы с json
api = overpy.Overpass() #relation["healthcare"="clinic"];

база = []
r = api.query("""
(way["healthcare"="clinic"]
  (55.57494,37.55671,55.69486,37.62807);
rel["healthcare"="clinic"]
  (55.57494,37.55671,55.69486,37.62807);
node["healthcare"="clinic"]
  (55.57494,37.55671,55.69486,37.62807););
out center;
""")
#print(r.relations)
#print(r.nodes)
for i in r.ways:
	i.tags.update({'ш' : str(i.center_lat), 'д' : str(i.center_lon), })
	база.append(i.tags)
for i in r.relations:
	i.tags.update({'ш' : str(i.center_lat), 'д' : str(i.center_lon), })
	база.append(i.tags)
for i in r.nodes:
	i.tags.update({'ш' : str(i.lat), 'д' : str(i.lon), })
	база.append(i.tags)
print(json.dumps(база, ensure_ascii = False))