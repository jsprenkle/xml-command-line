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
CND_CONF=Linux_Release
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/jcapimin.o \
	${OBJECTDIR}/jcapistd.o \
	${OBJECTDIR}/jccoefct.o \
	${OBJECTDIR}/jccolor.o \
	${OBJECTDIR}/jcdctmgr.o \
	${OBJECTDIR}/jchuff.o \
	${OBJECTDIR}/jcinit.o \
	${OBJECTDIR}/jcmainct.o \
	${OBJECTDIR}/jcmarker.o \
	${OBJECTDIR}/jcmaster.o \
	${OBJECTDIR}/jcomapi.o \
	${OBJECTDIR}/jcparam.o \
	${OBJECTDIR}/jcphuff.o \
	${OBJECTDIR}/jcprepct.o \
	${OBJECTDIR}/jcsample.o \
	${OBJECTDIR}/jdatadst.o \
	${OBJECTDIR}/jerror.o \
	${OBJECTDIR}/jfdctflt.o \
	${OBJECTDIR}/jfdctfst.o \
	${OBJECTDIR}/jfdctint.o \
	${OBJECTDIR}/jmemmgr.o \
	${OBJECTDIR}/jmemnobs.o \
	${OBJECTDIR}/jsimd_none.o \
	${OBJECTDIR}/jutils.o


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
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libjpglib.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libjpglib.a: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libjpglib.a
	${AR} -rv ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libjpglib.a ${OBJECTFILES} 
	$(RANLIB) ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libjpglib.a

${OBJECTDIR}/jcapimin.o: jcapimin.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.c) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/jcapimin.o jcapimin.c

${OBJECTDIR}/jcapistd.o: jcapistd.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.c) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/jcapistd.o jcapistd.c

${OBJECTDIR}/jccoefct.o: jccoefct.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.c) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/jccoefct.o jccoefct.c

${OBJECTDIR}/jccolor.o: jccolor.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.c) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/jccolor.o jccolor.c

${OBJECTDIR}/jcdctmgr.o: jcdctmgr.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.c) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/jcdctmgr.o jcdctmgr.c

${OBJECTDIR}/jchuff.o: jchuff.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.c) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/jchuff.o jchuff.c

${OBJECTDIR}/jcinit.o: jcinit.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.c) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/jcinit.o jcinit.c

${OBJECTDIR}/jcmainct.o: jcmainct.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.c) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/jcmainct.o jcmainct.c

${OBJECTDIR}/jcmarker.o: jcmarker.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.c) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/jcmarker.o jcmarker.c

${OBJECTDIR}/jcmaster.o: jcmaster.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.c) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/jcmaster.o jcmaster.c

${OBJECTDIR}/jcomapi.o: jcomapi.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.c) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/jcomapi.o jcomapi.c

${OBJECTDIR}/jcparam.o: jcparam.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.c) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/jcparam.o jcparam.c

${OBJECTDIR}/jcphuff.o: jcphuff.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.c) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/jcphuff.o jcphuff.c

${OBJECTDIR}/jcprepct.o: jcprepct.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.c) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/jcprepct.o jcprepct.c

${OBJECTDIR}/jcsample.o: jcsample.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.c) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/jcsample.o jcsample.c

${OBJECTDIR}/jdatadst.o: jdatadst.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.c) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/jdatadst.o jdatadst.c

${OBJECTDIR}/jerror.o: jerror.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.c) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/jerror.o jerror.c

${OBJECTDIR}/jfdctflt.o: jfdctflt.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.c) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/jfdctflt.o jfdctflt.c

${OBJECTDIR}/jfdctfst.o: jfdctfst.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.c) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/jfdctfst.o jfdctfst.c

${OBJECTDIR}/jfdctint.o: jfdctint.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.c) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/jfdctint.o jfdctint.c

${OBJECTDIR}/jmemmgr.o: jmemmgr.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.c) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/jmemmgr.o jmemmgr.c

${OBJECTDIR}/jmemnobs.o: jmemnobs.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.c) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/jmemnobs.o jmemnobs.c

${OBJECTDIR}/jsimd_none.o: jsimd_none.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.c) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/jsimd_none.o jsimd_none.c

${OBJECTDIR}/jutils.o: jutils.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.c) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/jutils.o jutils.c

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libjpglib.a

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
