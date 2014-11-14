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
CCC=g++
CXX=g++
FC=gfortran
AS=as

# Macros
CND_PLATFORM=MinGW-Windows
CND_DLIB_EXT=dll
CND_CONF=Release
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/XmlUnion.App.o \
	${OBJECTDIR}/XmlUnion.Config.Reader.o \
	${OBJECTDIR}/XmlUnion.Config.Settings.o \
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
LDLIBSOPTIONS=../XmlCmd/dist/Release/MinGW-Windows/libxmlcmd.a

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/XmlUnion.exe

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/XmlUnion.exe: ../XmlCmd/dist/Release/MinGW-Windows/libxmlcmd.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/XmlUnion.exe: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/XmlUnion ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/XmlUnion.App.o: XmlUnion.App.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -I. -I../XmlCmd -I../rapidxml-1.13 -MMD -MP -MF $@.d -o ${OBJECTDIR}/XmlUnion.App.o XmlUnion.App.cpp

${OBJECTDIR}/XmlUnion.Config.Reader.o: XmlUnion.Config.Reader.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -I. -I../XmlCmd -I../rapidxml-1.13 -MMD -MP -MF $@.d -o ${OBJECTDIR}/XmlUnion.Config.Reader.o XmlUnion.Config.Reader.cpp

${OBJECTDIR}/XmlUnion.Config.Settings.o: XmlUnion.Config.Settings.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -I. -I../XmlCmd -I../rapidxml-1.13 -MMD -MP -MF $@.d -o ${OBJECTDIR}/XmlUnion.Config.Settings.o XmlUnion.Config.Settings.cpp

${OBJECTDIR}/main.o: main.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -I. -I../XmlCmd -I../rapidxml-1.13 -MMD -MP -MF $@.d -o ${OBJECTDIR}/main.o main.cpp

# Subprojects
.build-subprojects:
	cd ../XmlCmd && ${MAKE}  -f Makefile CONF=Release

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/XmlUnion.exe

# Subprojects
.clean-subprojects:
	cd ../XmlCmd && ${MAKE}  -f Makefile CONF=Release clean

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
