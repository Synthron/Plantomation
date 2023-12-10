import os

path_page_main = os.path.join("src", "html", "main.html")
path_page_config = os.path.join("src", "html", "config.html")
path_page_about = os.path.join("src", "html", "about.html")

path_header = os.path.join("src", "sites.h")

f = open(path_page_main, "r")
content_main = f.read()
f.close()

f = open(path_page_config, "r")
content_config = f.read()
f.close()

f = open(path_page_about, "r")
content_about = f.read()
f.close()

os.remove(path_header)
f = open(path_header, "w")

f.write("const char MAIN_page[] = R\"=====(\n")
f.write(content_main)
f.write(")=====\";\n\n")

f.write("const char CONFIG_page[] = R\"=====(\n")
f.write(content_config)
f.write(")=====\";\n\n")

f.write("const char ABOUT_page[] = R\"=====(\n")
f.write(content_about)
f.write(")=====\";")

f.close()

