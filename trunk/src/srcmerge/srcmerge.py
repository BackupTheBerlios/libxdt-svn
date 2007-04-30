################################################################################
# imports
from __future__	import with_statement
from datetime	import datetime
from optparse	import OptionParser
from fnmatch	import fnmatch
import sys, re, os


################################################################################
# our global constants to use
args = sys.argv
argc = len(args)
script_name 	= os.path.basename(args[0])
src_signature	= '/'*80 + '\n' + '// %s: auto generated at %s\n'
src_info_hdr	= '// %s: + %s\n'
src_info_line	= '\n\n' + '/'*80 + '\n' + '// %s: %s\n'
src_include_hdr	= '\n\n' + '/'*80 + '\n' + '// %s: forced includes\n'
src_include		= '#include %s	// %s: included\n'
rex_include		= re.compile('\\s*#\\s*include\\s*(?P<inc>(<.+>)|(\\".+\\"))')
src_excluded	= '// %s: #include %s	// excluded'

opt_parser		= OptionParser()
opt_parser.add_option('-D', '--directory', action='append',
					  dest='dirs', metavar='DIRECTORY',
					  help='Adds files from directory',
					  default = [])
opt_parser.add_option('-S', '--source', action='append',
					  dest='sources', metavar='FILE',
					  help='Adds source file (.cpp)',
					  default = [])
opt_parser.add_option('-H', '--header', action='append',
					  dest='headers', metavar='FILE',
					  help='Adds header file (.h)',
					  default = [])
opt_parser.add_option('-i', '--include', action='append',
					  dest='includes', metavar='INCLUDE',
					  help='Adds file to includes list',
					  default = [])
opt_parser.add_option('-e', '--exclude', action='append',
					  dest='excludes', metavar='INCLUDE',
					  help='Adds file to excludes list',
					  default = [])
opt_parser.add_option('-r', '--mheader', action='store',
					  dest='merged_header', metavar='FILE',
					  help='File to merge in headers',
					  default = [])
opt_parser.add_option('-c', '--msource', action='store',
					  dest='merged_source', metavar='FILE',
					  help='File to merge in sources',
					  default = [])


################################################################################
# functions

def merge_files(files, merged, includes = [], excludes = []):
	"""
	Merge files
	files		- list of files (file path list) to merge
	merged		- path fo file, where to put result
	includes	- files to include in merged result
	excludes	- include files to exclude from merge result
	return		- all included names (used in '#include *' directive)
	"""
	with open(merged, 'w') as hmerged:
		# write merged file signature header
		hmerged.write(src_signature % (script_name, str(datetime.today())))

		for file_name in files:
			hmerged.write(src_info_hdr % (script_name, file_name))

		if 0 < len(includes):
			hmerged.write(src_include_hdr % (script_name))
			for item in includes:
				hmerged.write(src_include % (item, script_name))

		included = []

		for file_name in files:
			hmerged.write(src_info_line % (script_name, file_name))
			with open(file_name, 'r')  as hfile:
				for line in hfile:
					m = rex_include.match(line)
					if not m:
						# non '#include *' line - write it as is
						hmerged.write(line)
					else:
						# '#include *' line
						inc = m.group('inc')
						if inc in excludes:
							hmerged.write(src_excluded % (script_name, inc))
						else:
							included.append(inc)
							hmerged.write(line)

		return included


def walk_dirs(dirs):
	"""
	return		- (headers, sources)
	"""
	headers = []
	sources = []

	for dir in dirs:
		for root, dirs, files in os.walk(dir):
			for file_name in files:
				path = os.path.join(root, file_name)
				if fnmatch(path, '*.h'): headers.append(path)
				elif fnmatch(path, '*.cpp'): sources.append(path)

	return (headers, sources)


################################################################################
# main function
def main():
	

	(options, arguments) =  opt_parser.parse_args()

	(dir_headers, dir_sources) = walk_dirs(options.dirs)

	header_files = options.headers + dir_headers
	source_files = options.sources + dir_sources

	merged_header = options.merged_header
	merged_source = options.merged_source

	if header_files and merged_header:
		merge_files(header_files, merged_header,
					includes = options.includes,
					excludes = options.excludes)

	if source_files and merged_source:
		merge_files(source_files, merged_source,
					includes = options.includes,
					excludes = options.excludes)


################################################################################
# execute
if __name__ == "__main__":
	main()
