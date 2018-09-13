# DO NOT EDIT
# This makefile makes sure all linkable targets are
# up-to-date with anything they link to
default:
	echo "Do not invoke directly"

# Rules to remove targets that are older than anything to which they
# link.  This forces Xcode to relink the targets from scratch.  It
# does not seem to check these dependencies itself.
PostBuild.tsp.Debug:
/Users/admin/Documents/0x0/Repositories/tsp/build/Debug/tsp:
	/bin/rm -f /Users/admin/Documents/0x0/Repositories/tsp/build/Debug/tsp


PostBuild.tsp.Release:
/Users/admin/Documents/0x0/Repositories/tsp/build/Release/tsp:
	/bin/rm -f /Users/admin/Documents/0x0/Repositories/tsp/build/Release/tsp


PostBuild.tsp.MinSizeRel:
/Users/admin/Documents/0x0/Repositories/tsp/build/MinSizeRel/tsp:
	/bin/rm -f /Users/admin/Documents/0x0/Repositories/tsp/build/MinSizeRel/tsp


PostBuild.tsp.RelWithDebInfo:
/Users/admin/Documents/0x0/Repositories/tsp/build/RelWithDebInfo/tsp:
	/bin/rm -f /Users/admin/Documents/0x0/Repositories/tsp/build/RelWithDebInfo/tsp




# For each target create a dummy ruleso the target does not have to exist
