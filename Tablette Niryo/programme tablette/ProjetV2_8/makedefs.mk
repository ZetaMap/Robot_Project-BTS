COMPILER=gcc
PREFIX=arm-none-eabi
CC=${PREFIX}-gcc
CPU=-mcpu=cortex-m4
FPU=-mfpu=fpv4-sp-d16 -mfloat-abi=softfp

IPATH=.
IPATH+=${ROOT}/include

AFLAGS=-mthumb \
       ${CPU}  \
       ${FPU}  \
       -MD

CFLAGS=-mthumb             \
       ${CPU}              \
       ${FPU}              \
       -ffunction-sections \
       -fdata-sections     \
       -mpure-code         \
       -MD                 \
       -std=c99            \
       -Wall               \
       -pedantic           \
       -DPART_${PART}      \
       -c

AR=${PREFIX}-ar
LD=${PREFIX}-ld
LDFLAGS=--gc-sections
LIBGCC:=${shell ${CC} ${CFLAGS} -print-libgcc-file-name}
LIBC:=${shell ${CC} ${CFLAGS} -print-file-name=libc.a}
LIBM:=${shell ${CC} ${CFLAGS} -print-file-name=libm.a}
OBJCOPY=${PREFIX}-objcopy

ifdef DEBUG
CFLAGS+=-g -D DEBUG -O0
else
CFLAGS+=-O1
endif

CFLAGS+=${CFLAGSgcc}

AFLAGS+=${patsubst %,-I%,${subst :, ,${IPATH}}}
CFLAGS+=${patsubst %,-I%,${subst :, ,${IPATH}}}

#
# The rule for building the object file from each C source file.
#
%.o: %.c
	@if [ 'x${VERBOSE}' = x ];                            \
	 then                                                 \
	     echo "  CC    ${<}";                             \
	 else                                                 \
	     echo ${CC} ${CFLAGS} -D${COMPILER} -o ${@} ${<}; \
	 fi
	@${CC} ${CFLAGS} -D${COMPILER} -o ${@} ${<}
ifneq ($(findstring CYGWIN, ${os}), )
	@if [ -e ${@:.o=.d} ];                                   \
	then                                                     \
		sed -i -r 's/ ([A-Za-z]):/ \/cygdrive\/\1/g' ${@:.o=.d} ; \
	fi
endif

#
# The rule for building the object file from each assembly source file.
#
${COMPILER}${SUFFIX}/%.o: %.S
	@if [ 'x${VERBOSE}' = x ];                               \
	 then                                                    \
	     echo "  AS    ${<}";                                \
	 else                                                    \
	     echo ${CC} ${AFLAGS} -D${COMPILER} -o ${@} -c ${<}; \
	 fi
	@${CC} ${AFLAGS} -D${COMPILER} -o ${@} -c ${<}
ifneq ($(findstring CYGWIN, ${os}), )
	@if [ -e ${@:.o=.d} ];                                   \
	then                                                     \
		sed -i -r 's/ ([A-Za-z]):/ \/cygdrive\/\1/g' ${@:.o=.d} ; \
	fi
endif

#
# The rule for creating an object library.
#
${COMPILER}${SUFFIX}/%.a:
	@if [ 'x${VERBOSE}' = x ];     \
	 then                          \
	     echo "  AR    ${@}";      \
	 else                          \
	     echo ${AR} -cr ${@} ${^}; \
	 fi
	@${AR} -cr ${@} ${^}

#
# The rule for linking the application.
#
%.axf:
	@if [ 'x${SCATTERgcc_${notdir ${@:.axf=}}}' = x ];                    \
	 then                                                                 \
	     ldname="${ROOT}/gcc/standalone.ld";                              \
	 else                                                                 \
	     ldname="${SCATTERgcc_${notdir ${@:.axf=}}}";                     \
	 fi;                                                                  \
	 if [ 'x${VERBOSE}' = x ];                                            \
	 then                                                                 \
	     echo "  LD    ${@} ${LNK_SCP}";                                  \
	 else                                                                 \
	     echo ${LD} -T $${ldname}                                         \
	          --entry ${ENTRY_${notdir ${@:.axf=}}}                       \
	          ${LDFLAGSgcc_${notdir ${@:.axf=}}}                          \
	          ${LDFLAGS} -o ${@} $(filter %.o %.a, ${^})                  \
	          '${LIBM}' '${LIBC}' '${LIBGCC}';                            \
	 fi;                                                                  \
	${LD} -T $${ldname}                                                   \
	      --entry 100 ${ENTRY_${notdir ${@:.axf=}}}                           \
	      ${LDFLAGSgcc_${notdir ${@:.axf=}}}                              \
	      ${LDFLAGS} -o ${@} $(filter %.o %.a, ${^})                      \
	      '${LIBM}' '${LIBC}' '${LIBGCC}'
	@${OBJCOPY} -O binary ${@} ${@:.axf=.bin}
	@echo ""
	@${PREFIX}-size --format=berkeley ${@}
	@echo Program Image Built!
#	@chksize.sh ${TARGET}.bin 1032192 imgd.bin 8388608
#@echo Congratulation! HMIWorks of ICP DAS builds successfully.
