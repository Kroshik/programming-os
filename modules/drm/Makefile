# $FreeBSD: releng/10.3/sys/modules/drm/Makefile 230972 2012-02-04 00:54:43Z rmh $

.include <bsd.own.mk>

# Modules that include binary-only blobs of microcode should be selectable by
# MK_SOURCELESS_UCODE option (see below).

SUBDIR = \
	drm \
	i915 \
	mach64 \
	${_mga} \
	${_r128} \
	${_radeon} \
	savage \
	sis \
	tdfx \
	via

.if ${MK_SOURCELESS_UCODE} != "no"
_mga=		mga
_r128=		r128
_radeon=	radeon
.endif

.include <bsd.subdir.mk>
