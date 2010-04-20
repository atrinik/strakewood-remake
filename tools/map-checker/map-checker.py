#!/usr/bin/python
#
# Application to check Atrinik maps for common errors.

import sys, os, getopt

# We will need some recursion.
sys.setrecursionlimit(50000)

# Defines for different types of errors.
class errors:
	# A warning; often not an error, but should be checked anyway.
	warning = 0
	# Low priority.
	low = 1
	# Medium.
	medium = 2
	# High.
	high = 3
	# A critical error.
	critical = 4

	# Text representations of the above.
	text = ["WARNING", "LOW", "MEDIUM", "HIGH", "CRITICAL"]
	# ANSI escape sequences to make colors for above errors.
	colors = ["\033[30m", "\033[35m", "\033[36m", "\033[34m", "\033[31m"]
	# Pango (Hex/word) colors for above errors.
	pango_colors = ["black", "magenta", "cyan", "blue", "red"]

# Common escape sequences.
class colors:
	bold = "\033[1m"
	underscore = "\033[4m"
	end = "\033[0m"

# Object types.
class types:
	spawn_point = 81

# Configuration related to the application and some other defines.
class checker:
	# Name of the application.
	name = "Atrinik Map Checker"
	# Version.
	version = "1.0"
	# Copyright.
	copyright = "Copyright \xc2\xa9 2010 Atrinik Development Team"
	# GNU GPL license.
	license = "This program is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation; either version 2 of the License, or (at your option) any later version.\n\nThis program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details.\n\nYou should have received a copy of the GNU General Public License along with this program; if not, write to the Free Software Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA."
	# Description of the application.
	description = "Application to check Atrinik maps for common errors."
	# Authors.
	authors = ["Alex Tokar"]
	# Website URL.
	website = "http://www.atrinik.org/"
	# Website URL for reporting bugs in the application.
	website_bug = "http://bugzilla.atrinik.org/"

	# Highest layer value any archetype can have.
	max_layers = 7

# Print usage.
def usage():
	print("\n" + colors.bold + colors.underscore + "Use:" + colors.end + colors.end)
	print("\nGUI/CLI application to check Atrinik maps for common errors.\n")
	print(colors.bold + colors.underscore + "Options:" + colors.end + colors.end)
	print("\n\t-h, --help:\n\t\tDisplay this help.")
	print("\n\t-c, --cli:\n\t\tCommand Line Interface mode. Default is to start in GUI.")
	print("\n\t-d " + colors.underscore + "directory" + colors.end + ", --directory=" + colors.underscore + "directory" + colors.end + ":\n\t\tSpecify directory where to start checking map files (recursively). Default is '../../maps'.")
	print("\n\t-a " + colors.underscore + "arch" + colors.end + ", --arch=" + colors.underscore + "arch" + colors.end + ":\n\t\tSpecify where 'arch' directory is located (to get artifacts, archetypes, etc from). Default is '../../arch'.")
	print("\n\t-r " + colors.underscore + "file" + colors.end + ", --regions=" + colors.underscore + "file" + colors.end + ":\n\t\tSpecify where the 'regions.reg' file is located. Default is '../../maps/regions.reg.")
	print("\n\t-m " + colors.underscore + "map" + colors.end + ", --map=" + colors.underscore + "map" + colors.end + ":\n\t\tSpecify the only map to check for errors.")

# Try to parse our command line options.
try:
	opts, args = getopt.getopt(sys.argv[1:], "hcd:m:a:r:", ["help", "cli", "directory=", "map=", "arch=", "regions="])
except getopt.GetoptError as err:
	# Invalid option, show the error, print usage, and exit.
	print(err)
	usage()
	sys.exit(2)

# The default values.
path = "../../maps"
arch_dir = "../../arch"
regions_file = "../../maps/regions.reg"
map = None
cli = False

# Parse options.
for o, a in opts:
	if o in ("-h", "--help"):
		usage()
		sys.exit()
	elif o in ("-c", "--cli"):
		cli = True
	elif o in ("-d", "--directory"):
		path = a
	elif o in ("-m", "--map"):
		map = a
	elif o in ("-a", "--arch"):
		arch_dir = a
	elif o in ("-r", "--regions"):
		regions_file = a

# Errors we found in maps/objects.
errors_d = {}
# Errors from artifacts file.
errors_artifacts = []
# Errors from archetypes file.
errors_archetypes = []
# Errors from regions file.
errors_regions = []
# Configuration options.
config = {}
# Loaded archetypes.
archetypes = {}
# Artifacts.
artifacts = {}
# Regions.
regions = {}

# Add error to errors_d.
# @param map Map file.
# @param msg Description of the error.
# @param severity Severity of the error, from 'errors'.
# @param x X position of object.
# @param y Y position of object.
def add_error(map, msg, severity, x = -1, y = -1):
	if not map in errors_d:
		errors_d[map] = []

	# Add the error.
	errors_d[map].append([msg, severity, x, y])

# Load the map.
# @param fp File pointer.
# @return Dictionary of the map data, empty dictionary if the map
# is not valid.
def load_map(fp):
	d = {}
	in_map = False
	in_msg = False
	msg_buf = ""

	for line in fp:
		if line == "arch map\n":
			in_map = True
			continue
		elif not in_map:
			return {}
		elif line == "end\n":
			# Store the map's file name.
			d["file"] = fp.name

			# Strip off 'path' if possible.
			if d["file"][:len(path)] == path:
				d["file"] = d["file"][len(path) + 1:]

			# Load the objects on this map.
			parser = ObjectParser(fp)
			d["tiles"] = parser.map(d["file"])

			return d

		# Start of message.
		if line == "msg\n":
			in_msg = True
		# End of message.
		elif line == "endmsg\n":
			in_msg = False
			# Add it to the dictionary, removing the last newline.
			d["msg"] = msg_buf[:-1]
		# Store it in a buffer.
		elif in_msg:
			msg_buf += line
		# Map's attributes.
		else:
			space_pos = line.find(" ")
			# Our value.
			value = line[space_pos + 1:-1]

			if isint(value):
				value = int(value)

			# Add it to the dictionary.
			d[line[:space_pos]] = value

	return {}

# Check map.
# @param map Map to check.
def check_map(map):
	tiles = []

	# Go through the attributes.
	for attribute in map:
		if attribute[:10] == "tile_path_":
			# Map being tiled into itself is a critical error.
			if map["file"][len(map["file"]) - len(map[attribute]):] == map[attribute]:
				add_error(map["file"], "Map is tiled into itself (tile #{9}).".format(attribute[10:]), errors.critical)
				continue

			# Map having two same tiles is also a critical error.
			for tile in tiles:
				if tile == map[attribute]:
					add_error(map["file"], "Map is tiled to '{0}' more than once.".format(tile), errors.critical)

			tiles.append(map[attribute])

	# No difficulty? Not really an error, but the server will drop a warning and change
	# the difficulty to 1.
	if not "difficulty" in map:
		add_error(map["file"], "Map is missing difficulty.", errors.low)
	# This is an error, if the difficulty is set, and it's lower than 1 or higher than 110.
	elif map["difficulty"] < 1 or map["difficulty"] > 110:
		add_error(map["file"], "Map has invalid difficulty: {0}. Valid difficulties are 1-110.".format(map["difficulty"]), errors.medium)

	# Map missing 'width' or 'height' is a serious error.
	if not "width" in map:
		add_error(map["file"], "Map is missing width.", errors.high)

	if not "height" in map:
		add_error(map["file"], "Map is missing height.", errors.high)

	# Do we have a region, but it's not a valid one?
	if "region" in map and not map["region"] in regions:
		add_error(map["file"], "Map's region '{0}' is not defined in regions.reg file.".format(map["region"]), errors.high)

	# If there is no height or width, there's no point going on.
	if not "height" or not "width":
		return

	# Go through all the spaces on the map.
	for x in range(0, map["width"]):
		for y in range(0, map["height"]):
			if not x in map["tiles"] or not y in map["tiles"][x]:
				continue

			# Our layers.
			layers = [0] * (checker.max_layers + 1)
			# Number of objects. Layer 0 objects are not counted.
			obj_count = 0
			# Total number of objects, with layer 0 objects.
			obj_count_all = 0

			# Go through the objects on this map space.
			for obj in map["tiles"][x][y]:
				# Get our layer.
				layer = "layer" in obj and obj["layer"] or 0
				# Increase number of layers.
				layers[layer] += 1

				# Increase number of objects, if we're not on layer 0.
				if layer != 0:
					obj_count += 1

				# The total count of objects.
				obj_count_all += 1

				# Now recursively check the object.
				check_obj(obj, map["file"])

			# No layer 1 objects and there are other non-layer-0 objects? Missing floor.
			if layers[1] == 0 and obj_count > 0:
				add_error(map["file"], "Missing layer 1 object on tile with some objects -- missing floor?", errors.medium, x, y)

			# Go through the layers (ignoring layer 0), and check if we have more than one
			# object of the same layer on this space.
			for i in range(1, checker.max_layers):
				if layers[i] > 1:
					add_error(map["file"], "More than 1 object ({0}) with layer {1} on same tile.".format(layers[i], i), errors.warning, x, y)

# Recursively check object.
# @param obj Object to check.
# @param map Map's file name the object is on.
def check_obj(obj, map):
	# Check all inventory objects.
	for obj_inv in obj["inv"]:
		check_obj(obj_inv, map)

	# Spawn point without an inventory is an error.
	if "type" in obj and obj["type"] == types.spawn_point and not obj["inv"]:
		add_error(map, "Empty spawn point object.", errors.medium, obj["x"], obj["y"])

	if "env" in obj:
		env = get_env(obj)

		if "x" in obj:
			add_error(map, "Object '{0}' has X position set but is in inventory of another object.".format(obj["archname"]), errors.medium, env["x"], env["y"])

		if "y" in obj:
			add_error(map, "Object '{0}' has Y position set but is in inventory of another object.".format(obj["archname"]), errors.medium, env["x"], env["y"])

# Load map. If successfully loaded, we will check the map header
# and its objects with check_map().
# @param file Map to load.
def check_file(file):
	fp = open(file, "r")
	map = load_map(fp)
	fp.close()

	if map:
		check_map(map)

# Recursively scan directiores and call check_file on found files.
# @param dir Directory to scan.
def scan_dirs(dir):
	files = os.listdir(dir)

	for file in files:
		if os.path.isdir(dir + "/" + file):
			# Skip obvious non-map directories. It's still possible to scan those
			# if you pass --directory option however.
			if file in ("styles", "python"):
				continue

			scan_dirs(dir + "/" + file)
		else:
			check_file(dir + "/" + file)

# Do the scan. If 'map' argument was specified, we will use that,
# otherwise we will recursively scan 'path'.
def do_scan():
	if map:
		check_file(map)
	else:
		scan_dirs(path)

# Try to find an archetype by its arch name. This will also consider artifacts
# as archetypes.
# @param archname Arch name to find.
# @return The arch (or artifact) if found, None otherwise.
def get_archetype(archname):
	if archname in archetypes:
		return dict(archetypes[archname])
	elif archname in artifacts:
		return dict(artifacts[archname])

	return None

# Recursively look through object's environment value.
# @param obj Object.
# @return Object on map that has this object somewhere in its inventory.
def get_env(obj):
	ret = obj

	while "env" in ret:
		ret = ret["env"]

	return ret

# Check whether the passed string is an integer.
# @param s String.
# @return True if s is an integer, False otherwise.
def isint(s):
	try:
		int(s)
		return True
	except ValueError:
		return False

# Object parser.
class ObjectParser:
	# Initializer.
	# @param fp File pointer to read data from.
	def __init__(self, fp):
		self.fp = fp
		self.dict = {}
		self.last_obj = None
		self.in_msg = False
		self.msg_buf = ""
		self.line_num = 0

	# Archetypes parser.
	# @return Archetypes.
	def archetypes(self):
		for line in self.fp:
			self.line_num += 1

			if line[:7] == "Object ":
				self.last_obj = line[7:-1]
				self.dict[self.last_obj] = {}
				continue
			elif not self.last_obj:
				continue
			elif line == "end\n":
				self.last_obj = None
				continue

			# Parse attributes.
			self.parse(line, self.dict[self.last_obj])

		return self.dict

	# Artifacts parser.
	# @return Artifacts.
	def artifacts(self):
		for line in self.fp:
			self.line_num += 1

			if line[:9] == "artifact ":
				self.last_obj = line[9:-1]
				self.dict[self.last_obj] = {}
				continue
			elif not self.last_obj:
				continue
			elif line[:9] == "def_arch ":
				archetype = line[9:-1]

				if not archetype in archetypes:
					errors_artifacts.append(["Could not find archetype '{0}' for def_arch command (line: {1}).".format(archetype, self.line_num), errors.critical])
				else:
					self.dict[self.last_obj] = dict(archetypes[archetype])

				continue
			elif line == "end\n":
				self.last_obj = None
				continue

			# Parse attributes.
			self.parse(line, self.dict[self.last_obj])

		return self.dict

	# Map objects parser.
	# @param map_file Map file name we're loading objects for.
	# @return List of map tiles containing the found objects.
	def map(self, map_file):
		# Map tiles.
		self.tiles = {}
		self.map_file = map_file

		for line in self.fp:
			if line[:5] == "arch ":
				arch = self.map_parse_rec(line[5:-1])
				self.map_add_tile(arch)

		return self.tiles

	# Add object to map's tiles.
	# @param arch Object to add.
	def map_add_tile(self, arch):
		x = "x" in arch and arch["x"] or 0
		y = "y" in arch and arch["y"] or 0

		if not x in self.tiles:
			self.tiles[x] = {}

		if not y in self.tiles[x]:
			self.tiles[x][y] = []

		self.tiles[x][y].append(arch)

	# Recursively parse objects on map.
	# @param archname Arch name we previously found.
	# @return Archetype, complete with its inventory.
	def map_parse_rec(self, archname, env = None):
		# Find the archetype first.
		archetype = get_archetype(archname)
		invalid_arch = False

		# Could not find it? Drop an error about it, but continue loading.
		if not archetype:
			invalid_arch = True
			archetype = {}

		# Store its name.
		archetype["archname"] = archname
		# Inventory.
		archetype["inv"] = []

		if env:
			archetype["env"] = env

		for line in self.fp:
			# Another arch? That means it's inside the previous one.
			if line[:5] == "arch ":
				# Add it to the object's inventory.
				archetype["inv"].append(self.map_parse_rec(line[5:-1], archetype))
			elif line == "end\n":
				break
			# Parse attributes.
			else:
				self.parse(line, archetype)

		if invalid_arch:
			env = get_env(archetype)
			add_error(self.map_file, "Invalid archetype '{0}' found.".format(archetype["archname"]), errors.critical, "x" in env and env["x"] or 0, "y" in env and env["y"] or 0)

		return archetype

	# Parse attributes from a line.
	# @param line Line to parse from.
	# @param dict Dictionary add parsed attributes to.
	def parse(self, line, dict):
		# Message start?
		if line == "msg\n":
			self.in_msg = True
		# End of message.
		elif line == "endmsg\n":
			self.in_msg = False
			# Add it to the dict without the last newline.
			dict["msg"] = self.msg_buf[:-1]
		# We are in a message, store it in a buffer.
		elif self.in_msg:
			self.msg_buf += line
		# Not a message, so attribute/value combo.
		else:
			# Find space.
			space_pos = line.find(" ")
			# Our value.
			value = line[space_pos + 1:-1]

			if isint(value):
				value = int(value)

			# Add it to the dictionary.
			dict[line[:space_pos]] = value

# Parse the archetypes.
# @return Dictionary of the archetypes.
def parse_archetypes():
	fp = open(arch_dir + "/archetypes")
	parser = ObjectParser(fp)
	d = parser.archetypes()
	fp.close()
	return d

# Parse the artifacts.
# @return Dictionary of the artifacts.
def parse_artifacts():
	fp = open(arch_dir + "/artifacts")
	parser = ObjectParser(fp)
	d = parser.artifacts()
	fp.close()
	return d

# Parse the regions.
# @return Dictionary of the regions.
def parse_regions():
	fp = open(regions_file)
	d = {}
	region = None
	in_msg = False
	msg_buf = ""

	for line in fp:
		if line[:7] == "region ":
			region = line[7:-1]
			d[region] = {}
			continue
		elif not region:
			continue
		elif line == "end\n":
			region = None
			continue

		# Start of message.
		if line == "msg\n":
			in_msg = True
		# End of message.
		elif line == "endmsg\n":
			in_msg = False
			# Add it to the dictionary, removing the last newline.
			d[region]["msg"] = msg_buf[:-1]
		# Store it in a buffer.
		elif in_msg:
			msg_buf += line
		# Region's attributes.
		else:
			space_pos = line.find(" ")
			# Our value.
			value = line[space_pos + 1:-1]

			if isint(value):
				value = int(value)

			# Add it to the dictionary.
			d[region][line[:space_pos]] = value

	fp.close()
	return d

archetypes = parse_archetypes()
artifacts = parse_artifacts()
regions = parse_regions()

# GUI.
if not cli:
	try:
		import pygtk
		pygtk.require("2.0")
	except ImportError:
		print("PyGTK not found. Please make sure it is installed properly and referenced in your PYTHONPATH environment variable.")

	import gtk, re, webbrowser
	from datetime import datetime

	# The GUI class.
	class GUI:
		# Our UI, with menu and toolbar.
		ui = '''<ui>
<menubar name="MenuBar">
	<menu action="File">
		<menuitem action="Scan" />
		<menuitem action="Save" />
		<menuitem action="Check File" />
		<menuitem action="Check Directory" />
		<separator />
		<menuitem action="Quit" />
	</menu>
	<menu action="Suppress">
		<menuitem action="Warnings" />
		<menuitem action="Low" />
		<menuitem action="Medium" />
		<menuitem action="High" />
		<menuitem action="Critical" />
	</menu>
	<menu action="Reload">
		<menuitem action="Reload Archetypes" />
		<menuitem action="Reload Artifacts" />
		<menuitem action="Reload Regions" />
	</menu>
	<menu action="Help">
		<menuitem action="Report a Problem" />
		<menuitem action="About" />
	</menu>
</menubar>
<toolbar name="Toolbar">
	<toolitem action="Quit" />
	<separator />
	<toolitem action="Scan" />
	<toolitem action="Save" />
</toolbar>
</ui>'''

		# Initializer.
		def __init__(self):
			# Create a liststore.
			self.liststore = gtk.ListStore(str, str, str)

			# The window.
			self.window = gtk.Window(gtk.WINDOW_TOPLEVEL)
			# Set the title.
			self.window.set_title(checker.name)
			# 800x600 resolution.
			self.window.set_size_request(800, 600)
			self.window.connect("delete_event", self.quit_event)

			icon = self.find_icon()

			if icon:
				self.window.set_icon(icon)

			# New box.
			self.window.vbox = gtk.VBox()
			self.window.add(self.window.vbox)

			# Create UIManager instance.
			uimanager = gtk.UIManager()

			# Add the accelerator group to the toplevel window.
			accelgroup = uimanager.get_accel_group()
			self.window.add_accel_group(accelgroup)

			# Create an ActionGroup.
			self.actiongroup = gtk.ActionGroup("UIManager")

			# Create actions.
			self.actiongroup.add_actions([
				("File", None, "_File"),
				("Scan", gtk.STOCK_EXECUTE, "_Scan", "<control>s", "Scan maps", self.scan_button),
				("Save", gtk.STOCK_SAVE, "_Save", "<control><shift>s", "Save", self.save_button),
				("Check File", gtk.STOCK_OPEN, "_Check File", "<control>f", "Check File", self.check_file_button),
				("Check Directory", gtk.STOCK_DIRECTORY, "_Check Directory", "<control>d", "Check Directory", self.check_directory_button),
				("Quit", gtk.STOCK_QUIT, "_Quit", "<control>q", "Quit the program", self.quit_button),
				("Suppress", None, "_Suppress"),
				("Reload", None, "_Reload"),
				("Reload Archetypes", None, "_Reload Archetypes", None, "Reload archetypes from file", self.reload_archetypes_button),
				("Reload Artifacts", None, "_Reload Artifacts", None, "Reload artifacts from file", self.reload_artifacts_button),
				("Reload Regions", None, "_Reload Regions", None, "Reload regions from file", self.reload_regions_button),
				("Help", None, "_Help"),
				("Report a Problem", None, "_Report a Problem", None, "Report a Problem", self.report_button),
				("About", gtk.STOCK_ABOUT, "_About", None, "About this application", self.about_button),
			])

			# Create a toggle actions (checkboxes).
			self.actiongroup.add_toggle_actions([
				("Warnings", None, "_Warnings", None, "Suppress warnings", self.suppress_button0),
				("Low", None, "_Low", None, "Suppress low severity errors", self.suppress_button1),
				("Medium", None, "_Medium", None, "Suppress medium severity errors", self.suppress_button2),
				("High", None, "_High", None, "Suppress high severity errors", self.suppress_button3),
				("Critical", None, "_Critical", None, "Suppress critical errors", self.suppress_button4),
			])

			# Add the actiongroup to the UIManager.
			uimanager.insert_action_group(self.actiongroup, 0)

			# Add UI description.
			uimanager.add_ui_from_string(self.ui)

			# Create a MenuBar.
			menubar = uimanager.get_widget("/MenuBar")
			self.window.vbox.pack_start(menubar, False)

			# Create a Toolbar.
			toolbar = uimanager.get_widget("/Toolbar")
			self.window.vbox.pack_start(toolbar, False)

			# Create scrolled window.
			self.window.sw = gtk.ScrolledWindow()
			# So the scrollbars only appear if they're needed.
			self.window.sw.set_property("hscrollbar-policy", gtk.POLICY_AUTOMATIC)
			self.window.sw.set_property("vscrollbar-policy", gtk.POLICY_AUTOMATIC)

			# Tree model.
			self.window.sm = gtk.TreeModelSort(self.liststore)
			# Set sort column.
			self.window.sm.set_sort_column_id(0, gtk.SORT_ASCENDING)
			# Tree view.
			self.window.tv = gtk.TreeView(self.window.sm)
			self.window.vbox.pack_start(self.window.sw)

			self.window.sw.add(self.window.tv)

			# Our columns.
			columns = [
				["Map", False],
				["Severity", True],
				["Description", False],
			]
			self.window.tv.column = [None] * 3
			self.window.tv.cell = [None] * 3

			for i in range(3):
				self.window.tv.cell[i] = gtk.CellRendererText()

				# See if we want Pango markup or not.
				if columns[i][1]:
					self.window.tv.column[i] = gtk.TreeViewColumn(columns[i][0], self.window.tv.cell[i], markup = True)
				else:
					self.window.tv.column[i] = gtk.TreeViewColumn(columns[i][0])

				self.window.tv.append_column(self.window.tv.column[i])
				self.window.tv.column[i].set_sort_column_id(i)

				# Pango markup doesn't need this.
				if not columns[i][1]:
					self.window.tv.column[i].pack_start(self.window.tv.cell[i], True)
					self.window.tv.column[i].set_attributes(self.window.tv.cell[i], text = i)

			# Draw any errors (there can be some from things like artifacts, archetypes, etc)
			self.draw_errors()

			# Now show it all.
			self.window.show_all()

		# Event that happens when we quit the application (X at top right, ctrl + q, etc).
		def quit_event(self, widget, event, data = None):
			gtk.main_quit()
			return False

		# We pressed the quit button, so quit.
		def quit_button(self, b):
			gtk.main_quit()

		# The report button. Take us to the Atrinik Bugzilla.
		def report_button(self, b):
			webbrowser.open(checker.website_bug)

		# About button.
		def about_button(self, b):
			about = gtk.AboutDialog()
			about.set_transient_for(self.window)
			about.set_name(checker.name)
			about.set_version(checker.version)
			about.set_copyright(checker.copyright)
			about.set_license(checker.license)
			about.set_wrap_license(True)
			about.set_comments(checker.description)
			about.set_authors(checker.authors)
			about.set_website(checker.website)
			icon = self.find_icon()

			if icon:
				about.set_logo(icon)

			about.connect("response", lambda d, r: d.destroy())
			about.show()

		# The save button. Will save output in the tree view to file.
		def save_button(self, b):
			l = self.window.sm.get_model()

			# Nothing to save, display an error.
			if len(l) == 0:
				dialog = gtk.MessageDialog(self.window, 0, gtk.MESSAGE_ERROR, gtk.BUTTONS_CLOSE, "There are no errors to save!")
				dialog.show_all()
				dialog.run()
				dialog.destroy()
				return

			# Create the file chooser dialog.
			fc = gtk.FileChooserDialog("Save As...", None, gtk.FILE_CHOOSER_ACTION_SAVE, (gtk.STOCK_CANCEL, gtk.RESPONSE_CANCEL, gtk.STOCK_SAVE, gtk.RESPONSE_OK))
			# Set current directory.
			fc.set_current_folder(path)
			# Make up a file name that should be relatively unique.
			fc.set_current_name("atrinik_map_checker_" + datetime.now().strftime("%Y%m%d_%H-%M-%S") + ".txt")
			fc.set_default_response(gtk.RESPONSE_OK)
			response = fc.run()

			if response == gtk.RESPONSE_OK:
				# Now open the file name user chose for writing.
				fp = open(fc.get_filename(), "w")

				# Write the output to file. Note that we need to strip out Pango markup from 'severity'.
				for (map, severity, description) in l:
					fp.write("{0}: {1}: {2}\n".format(map, re.sub(r"<[^>]*?>", "", severity), description))

				fp.close()

			fc.destroy()

		# Common function for the below suppress_buttonx functions.
		def suppress_button(self, action, num):
			# Turn the config on/off.
			config["suppress_" + str(num)] = action.get_active()
			# Redraw the errors to update them.
			self.draw_errors()

		# Suppress button for 'warnings'.
		def suppress_button0(self, action):
			self.suppress_button(action, 0)

		# Suppress button for 'low'.
		def suppress_button1(self, action):
			self.suppress_button(action, 1)

		# Suppress button for 'medium'.
		def suppress_button2(self, action):
			self.suppress_button(action, 2)

		# Suppress button for 'high'.
		def suppress_button3(self, action):
			self.suppress_button(action, 3)

		# Suppress button for 'critical'.
		def suppress_button4(self, action):
			self.suppress_button(action, 4)

		# Action for the scan button.
		def scan_button(self, b):
			# Clear out old errors.
			errors_d.clear()
			# Re-scan.
			do_scan()
			# Draw the errors.
			self.draw_errors()

		# Check a directory of maps.
		def check_directory_button(self, b):
			# Create the file chooser dialog.
			fc = gtk.FileChooserDialog("Select Directory...", None, gtk.FILE_CHOOSER_ACTION_SELECT_FOLDER, (gtk.STOCK_CANCEL, gtk.RESPONSE_CANCEL, gtk.STOCK_OPEN, gtk.RESPONSE_OK))
			# Set current directory.
			fc.set_current_folder(path)
			fc.set_default_response(gtk.RESPONSE_OK)
			response = fc.run()

			if response == gtk.RESPONSE_OK:
				# Clear out old errors.
				errors_d.clear()
				# Scan the directory.
				scan_dirs(fc.get_filename())
				# Draw the errors.
				self.draw_errors()

			fc.destroy()

		# Check a single map.
		def check_file_button(self, b):
			# Create the file chooser dialog.
			fc = gtk.FileChooserDialog("Select File...", None, gtk.FILE_CHOOSER_ACTION_OPEN, (gtk.STOCK_CANCEL, gtk.RESPONSE_CANCEL, gtk.STOCK_OPEN, gtk.RESPONSE_OK))
			# Set current directory.
			fc.set_current_folder(path)
			fc.set_default_response(gtk.RESPONSE_OK)
			response = fc.run()

			if response == gtk.RESPONSE_OK:
				# Clear out old errors.
				errors_d.clear()
				# Check the map.
				check_file(fc.get_filename())
				# Draw errors.
				self.draw_errors()

			fc.destroy()

		# Reload archetypes.
		def reload_archetypes_button(self, b):
			archetypes = parse_archetypes()
			self.draw_errors()

		# Reload artifacts.
		def reload_artifacts_button(self, b):
			artifacts = parse_artifacts()
			self.draw_errors()

		# Reload regions.
		def reload_regions_button(self, b):
			regions = parse_regions()
			self.draw_errors()

		# Common function to draw one error.
		# @param error Error to draw.
		# @param file File the error is in.
		def draw_one_error(self, error, file):
			# Check if we have suppressed this kind of errors.
			if "suppress_" + str(error[1]) in config and config["suppress_" + str(error[1])]:
				return

			pos = ""

			# We are on map, so add X/Y coordinates after the error description.
			if len(error) > 2 and error[2] != -1 and error[3] != -1:
				pos = " (" + str(error[2]) + ", " + str(error[3]) + ")"

			# Add the error.
			self.window.sm.get_model().append([file, "<span foreground=\"" + errors.pango_colors[error[1]] + "\">" + errors.text[error[1]] + "</span>", error[0] + pos])

		# Draw the errors.
		def draw_errors(self):
			# Clear out old drawn errors.
			self.window.sm.get_model().clear()

			# Draw map errors.
			for map in errors_d:
				for error in errors_d[map]:
					self.draw_one_error(error, map)

			# Archetype errors.
			for error in errors_archetypes:
				self.draw_one_error(error, "Archetypes")

			# Artifact errors.
			for error in errors_artifacts:
				self.draw_one_error(error, "Artifacts")

			# Region errors.
			for error in errors_regions:
				self.draw_one_error(error, "Regions")

		# Try to find us an icon for the application.
		def find_icon(self):
			# Possible paths where our icon could be.
			paths = [
				"/usr/share/atrinik-client/bitmaps/icon.png",
				"../../client/bitmaps/icon.png",
			]

			for path in paths:
				if os.path.exists(path):
					return gtk.gdk.pixbuf_new_from_file(path)

	# Initialize the GUI.
	gui = GUI()
	gtk.main()
# CLI.
else:
	# Common function to print one error on the CLI.
	# @param error Error to print.
	# @param map Map. If not None, we are drawing an error on map, otherwise a different error (artifacts,
	# archetypes, etc).
	def print_one_error(error, map):
		pos = ""

		# We are on map, so add X/Y coordinates before the error description.
		if map and error[2] != -1 and error[3] != -1:
			pos = "(" + str(error[2]) + ", " + str(error[3]) + "): "

		print("  " + errors.colors[error[1]] + errors.text[error[1]] + colors.end + ": " + pos + error[0])

	# Start the scan.
	do_scan()
	print(colors.bold + colors.underscore + "Scan complete. Results:\n" + colors.end + colors.end)

	# Print map errors.
	for map in errors_d:
		print(colors.bold + map + ":" + colors.end)

		for error in errors_d[map]:
			print_one_error(error, map)

	# Archetype errors.
	if errors_archetypes:
		print(colors.bold + "Archetypes:" + colors.end)

		for error in errors_archetypes:
			print_one_error(error, None)

	# Artifact errors.
	if errors_artifacts:
		print(colors.bold + "Artifacts:" + colors.end)

		for error in errors_artifacts:
			print_one_error(error, None)

	# Region errors.
	if errors_regions:
		print(colors.bold + "Regions:" + colors.end)

		for error in errors_regions:
			print_one_error(error, None)