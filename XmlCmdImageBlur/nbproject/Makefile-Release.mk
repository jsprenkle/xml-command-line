#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
GREP=grep
NM=nm
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc
CCC=g++-4.7
CXX=g++-4.7
FC=gfortran
AS=as

# Macros
CND_PLATFORM=GNU-Linux-x86
CND_DLIB_EXT=so
CND_CONF=Release
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/XmlCmdImageBlur.App.o \
	${OBJECTDIR}/XmlCmdImageBlur.Config.Reader.o \
	${OBJECTDIR}/XmlCmdImageBlur.Config.Settings.o \
	${OBJECTDIR}/main.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=../XmlCmd/dist/Release/GNU-Linux-x86/libxmlcmd.a ../XmlCmdImage/dist/Release/GNU-Linux-x86/libxmlcmdimage.a

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/xmlcmdimageblur

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/xmlcmdimageblur: ../XmlCmd/dist/Release/GNU-Linux-x86/libxmlcmd.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/xmlcmdimageblur: ../XmlCmdImage/dist/Release/GNU-Linux-x86/libxmlcmdimage.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/xmlcmdimageblur: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/xmlcmdimageblur ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/XmlCmdImageBlur.App.o: XmlCmdImageBlur.App.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -I. -I../XmlCmd -I../XmlCmdImage -I../rapidxml-1.13 -MMD -MP -MF $@.d -o ${OBJECTDIR}/XmlCmdImageBlur.App.o XmlCmdImageBlur.App.cpp

${OBJECTDIR}/XmlCmdImageBlur.Config.Reader.o: XmlCmdImageBlur.Config.Reader.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -I. -I../XmlCmd -I../XmlCmdImage -I../rapidxml-1.13 -MMD -MP -MF $@.d -o ${OBJECTDIR}/XmlCmdImageBlur.Config.Reader.o XmlCmdImageBlur.Config.Reader.cpp

${OBJECTDIR}/XmlCmdImageBlur.Config.Settings.o: XmlCmdImageBlur.Config.Settings.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -I. -I../XmlCmd -I../XmlCmdImage -I../rapidxml-1.13 -MMD -MP -MF $@.d -o ${OBJECTDIR}/XmlCmdImageBlur.Config.Settings.o XmlCmdImageBlur.Config.Settings.cpp

${OBJECTDIR}/main.o: main.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -I. -I../XmlCmd -I../XmlCmdImage -I../rapidxml-1.13 -MMD -MP -MF $@.d -o ${OBJECTDIR}/main.o main.cpp

# Subprojects
.build-subprojects:
	cd ../XmlCmd && ${MAKE}  -f Makefile CONF=Release
	cd ../XmlCmdImage && ${MAKE}  -f Makefile CONF=Release

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/xmlcmdimageblur

# Subprojects
.clean-subprojects:
	cd ../XmlCmd && ${MAKE}  -f Makefile CONF=Release clean
	cd ../XmlCmdImage && ${MAKE}  -f Makefile CONF=Release clean

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
