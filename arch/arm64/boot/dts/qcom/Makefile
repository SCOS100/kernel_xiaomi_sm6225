# SPDX-License-Identifier: GPL-2.0
dtb-$(CONFIG_ARCH_QCOM)	+= apq8016-sbc.dtb
dtb-$(CONFIG_ARCH_QCOM)	+= apq8096-db820c.dtb
dtb-$(CONFIG_ARCH_QCOM)	+= ipq8074-hk01.dtb
dtb-$(CONFIG_ARCH_QCOM)	+= msm8916-mtp.dtb
dtb-$(CONFIG_ARCH_QCOM)	+= msm8992-bullhead-rev-101.dtb
dtb-$(CONFIG_ARCH_QCOM)	+= msm8994-angler-rev-101.dtb
dtb-$(CONFIG_ARCH_QCOM)	+= msm8996-mtp.dtb
dtb-$(CONFIG_ARCH_QCOM)	+= sdm845-mtp.dtb

ifeq ($(CONFIG_ARCH_KHAJE),y)
dtb-$(CONFIG_ARCH_QCOM) += sm6225-idp-nopmi.dtb
dtbo-$(CONFIG_ARCH_QCOM) += sm6225-xiaomi-spes-overlay.dtbo
sm6225-xiaomi-spes-overlay.dtbo-base += sm6225-idp-nopmi.dtb
#sm6225-xiaomi-spes-sm5602.dtbo-base += sm6225-idp-nopmi.dtb
#sm6225-xiaomi-spesn.dtbo-base += sm6225-idp-nopmi.dtb
endif

always		:= $(dtb-y)
subdir-y	:= $(dts-dirs)
clean-files    := *.dtb *.dtbo
