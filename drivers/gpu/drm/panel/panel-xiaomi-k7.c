// SPDX-License-Identifier: GPL-2.0-only
/*
 * Xiaomi K7 38 0C 0A / 0B OLED DSI Video Mode Panel Driver
 * Adapted for Qualcomm 4.19 kernel with older panel API
 */

#include <linux/delay.h>
#include <linux/gpio/consumer.h>
#include <linux/module.h>
#include <linux/of.h>
#include <linux/of_device.h>
#include <linux/regulator/consumer.h>
#include <drm/drm_mipi_dsi.h>
#include <drm/drm_modes.h>
#include <drm/drm_panel.h>

struct k7_panel {
	struct drm_panel panel;
	struct mipi_dsi_device *dsi;
	struct gpio_desc *reset_gpio;
	struct regulator *vddio;
	struct regulator *vci;
	const struct panel_desc *desc;
};

struct panel_desc {
	const struct drm_display_mode *mode;
	unsigned int width_mm;
	unsigned int height_mm;
	unsigned int lanes;
	int (*init)(struct k7_panel *p);
};

static inline struct k7_panel *to_k7_panel(struct drm_panel *panel)
{
	return container_of(panel, struct k7_panel, panel);
}

/* init sequences – same as before */
static int k7_0a_init(struct k7_panel *p)
{
	struct mipi_dsi_device *dsi = p->dsi;
	int ret;

	ret = mipi_dsi_dcs_write_buffer(dsi, (u8[]){ 0xb0, 0x00 }, 2);
	if (ret < 0) return ret;
	ret = mipi_dsi_dcs_write_buffer(dsi, (u8[]){ 0xb2, 0x01, 0x30 }, 3);
	if (ret < 0) return ret;
	ret = mipi_dsi_dcs_write_buffer(dsi, (u8[]){ 0xb0, 0x41 }, 2);
	if (ret < 0) return ret;
	ret = mipi_dsi_dcs_write_buffer(dsi, (u8[]){ 0xe0, 0x03 }, 2);
	if (ret < 0) return ret;
	ret = mipi_dsi_dcs_write_buffer(dsi, (u8[]){ 0xb0, 0x0d }, 2);
	if (ret < 0) return ret;
	ret = mipi_dsi_dcs_write_buffer(dsi, (u8[]){ 0xb2, 0x20 }, 2);
	if (ret < 0) return ret;
	ret = mipi_dsi_dcs_write_buffer(dsi, (u8[]){ 0xb0, 0x0c }, 2);
	if (ret < 0) return ret;
	ret = mipi_dsi_dcs_write_buffer(dsi, (u8[]){ 0xb2, 0x30 }, 2);
	if (ret < 0) return ret;
	ret = mipi_dsi_dcs_write_buffer(dsi, (u8[]){ 0x53, 0x30 }, 2);
	if (ret < 0) return ret;
	ret = mipi_dsi_dcs_write_buffer(dsi, (u8[]){ 0xf7, 0x07 }, 2);
	if (ret < 0) return ret;
	return 0;
}

static int k7_0b_init(struct k7_panel *p)
{
	struct mipi_dsi_device *dsi = p->dsi;
	int ret;

	ret = mipi_dsi_dcs_write_buffer(dsi, (u8[]){ 0xf0, 0x5a, 0x5a }, 3);
	if (ret < 0) return ret;
	ret = mipi_dsi_dcs_write_buffer(dsi, (u8[]){ 0xb2, 0x01, 0x31 }, 3);
	if (ret < 0) return ret;
	ret = mipi_dsi_dcs_write_buffer(dsi, (u8[]){ 0xf0, 0xa5, 0xa5 }, 3);
	if (ret < 0) return ret;
	ret = mipi_dsi_dcs_write_buffer(dsi, (u8[]){ 0xfc, 0x5a, 0x5a }, 3);
	if (ret < 0) return ret;
	ret = mipi_dsi_dcs_write_buffer(dsi, (u8[]){ 0xe1, 0x8b }, 2);
	if (ret < 0) return ret;
	ret = mipi_dsi_dcs_write_buffer(dsi, (u8[]){ 0xed, 0x00, 0x01 }, 3);
	if (ret < 0) return ret;
	ret = mipi_dsi_dcs_write_buffer(dsi, (u8[]){ 0xb0, 0x06 }, 2);
	if (ret < 0) return ret;
	ret = mipi_dsi_dcs_write_buffer(dsi, (u8[]){ 0xf4, 0x1f }, 2);
	if (ret < 0) return ret;
	ret = mipi_dsi_dcs_write_buffer(dsi, (u8[]){ 0xb0, 0x11 }, 2);
	if (ret < 0) return ret;
	ret = mipi_dsi_dcs_write_buffer(dsi, (u8[]){ 0xfe, 0x00 }, 2);
	if (ret < 0) return ret;
	ret = mipi_dsi_dcs_write_buffer(dsi, (u8[]){ 0x9d, 0x01 }, 2);
	if (ret < 0) return ret;
	ret = mipi_dsi_dcs_write_buffer(dsi, (u8[]){ 0xf0, 0x5a, 0x5a }, 3);
	if (ret < 0) return ret;
	ret = mipi_dsi_dcs_write_buffer(dsi, (u8[]){ 0x60, 0x21 }, 2);
	if (ret < 0) return ret;
	ret = mipi_dsi_dcs_write_buffer(dsi, (u8[]){ 0xf7, 0x0b }, 2);
	if (ret < 0) return ret;
	ret = mipi_dsi_dcs_write_buffer(dsi, (u8[]){ 0xb0, 0x0d }, 2);
	if (ret < 0) return ret;
	ret = mipi_dsi_dcs_write_buffer(dsi, (u8[]){ 0xb2, 0x20 }, 2);
	if (ret < 0) return ret;
	ret = mipi_dsi_dcs_write_buffer(dsi, (u8[]){ 0xb0, 0x0c }, 2);
	if (ret < 0) return ret;
	ret = mipi_dsi_dcs_write_buffer(dsi, (u8[]){ 0xb2, 0x30 }, 2);
	if (ret < 0) return ret;
	ret = mipi_dsi_dcs_write_buffer(dsi, (u8[]){ 0x53, 0x28 }, 2);
	if (ret < 0) return ret;
	ret = mipi_dsi_dcs_write_buffer(dsi, (u8[]){ 0xf7, 0x0b }, 2);
	if (ret < 0) return ret;
	ret = mipi_dsi_dcs_write_buffer(dsi, (u8[]){ 0xcd, 0x29, 0x00, 0x08 }, 4);
	if (ret < 0) return ret;
	ret = mipi_dsi_dcs_write_buffer(dsi, (u8[]){ 0xfc, 0x5a, 0x5a }, 3);
	if (ret < 0) return ret;
	ret = mipi_dsi_dcs_write_buffer(dsi, (u8[]){ 0xfe, 0xb0 }, 2);
	if (ret < 0) return ret;
	ret = mipi_dsi_dcs_write_buffer(dsi, (u8[]){ 0xfe, 0x30 }, 2);
	if (ret < 0) return ret;
	return 0;
}

static int k7_power_on(struct k7_panel *p)
{
	int ret;

	ret = regulator_enable(p->vci);
	if (ret)
		return ret;
	usleep_range(5000, 10000);

	ret = regulator_enable(p->vddio);
	if (ret)
		goto err_vddio;

	/* Reset sequence: active low reset */
	gpiod_set_value_cansleep(p->reset_gpio, 1); /* de-assert */
	usleep_range(10000, 20000);
	gpiod_set_value_cansleep(p->reset_gpio, 0); /* assert */
	usleep_range(10000, 20000);
	gpiod_set_value_cansleep(p->reset_gpio, 1); /* de-assert */
	msleep(20);
	return 0;

err_vddio:
	regulator_disable(p->vci);
	return ret;
}

static void k7_power_off(struct k7_panel *p)
{
	gpiod_set_value_cansleep(p->reset_gpio, 0);
	regulator_disable(p->vddio);
	regulator_disable(p->vci);
}

static int k7_panel_prepare(struct drm_panel *panel)
{
	struct k7_panel *p = to_k7_panel(panel);
	int ret;

	ret = k7_power_on(p);
	if (ret)
		return ret;

	if (p->desc->init) {
		ret = p->desc->init(p);
		if (ret)
			goto err;
	}

	ret = mipi_dsi_dcs_exit_sleep_mode(p->dsi);
	if (ret < 0)
		goto err;
	msleep(120);

	ret = mipi_dsi_dcs_set_display_on(p->dsi);
	if (ret < 0)
		goto err;
	return 0;

err:
	k7_power_off(p);
	return ret;
}

static int k7_panel_unprepare(struct drm_panel *panel)
{
	struct k7_panel *p = to_k7_panel(panel);
	int ret;

	ret = mipi_dsi_dcs_set_display_off(p->dsi);
	if (ret < 0)
		dev_err(&p->dsi->dev, "Failed to set display off: %d\n", ret);
	msleep(20);

	ret = mipi_dsi_dcs_enter_sleep_mode(p->dsi);
	if (ret < 0)
		dev_err(&p->dsi->dev, "Failed to enter sleep mode: %d\n", ret);
	msleep(60);

	k7_power_off(p);
	return 0;
}

static int k7_panel_get_modes(struct drm_panel *panel)
{
	/* In older kernels, the connector is accessible via panel->connector */
	struct k7_panel *p = to_k7_panel(panel);
	struct drm_connector *connector = panel->connector;
	struct drm_display_mode *mode;

	mode = drm_mode_duplicate(connector->dev, p->desc->mode);
	if (!mode)
		return -ENOMEM;

	drm_mode_set_name(mode);
	mode->type = DRM_MODE_TYPE_DRIVER | DRM_MODE_TYPE_PREFERRED;
	drm_mode_probed_add(connector, mode);

	connector->display_info.width_mm = p->desc->width_mm;
	connector->display_info.height_mm = p->desc->height_mm;
	return 1;
}

static const struct drm_panel_funcs k7_panel_funcs = {
	.prepare = k7_panel_prepare,
	.unprepare = k7_panel_unprepare,
	.get_modes = k7_panel_get_modes,
};

/* Timings: 1080x2400 @ 90Hz */
static const struct drm_display_mode k7_1080x2400_90hz = {
	.clock = 155770,
	.hdisplay = 1080,
	.hsync_start = 1080 + 320,
	.hsync_end   = 1080 + 320 + 32,
	.htotal      = 1080 + 320 + 32 + 120,
	.vdisplay = 2400,
	.vsync_start = 2400 + 20,
	.vsync_end   = 2400 + 20 + 2,
	.vtotal      = 2400 + 20 + 2 + 10,
	.flags = 0,
	.width_mm = 67,
	.height_mm = 149,
};

static const struct panel_desc k7_0a_desc = {
	.mode = &k7_1080x2400_90hz,
	.width_mm = 67,
	.height_mm = 149,
	.lanes = 4,
	.init = k7_0a_init,
};

static const struct panel_desc k7_0b_desc = {
	.mode = &k7_1080x2400_90hz,
	.width_mm = 67,
	.height_mm = 149,
	.lanes = 4,
	.init = k7_0b_init,
};

static int k7_panel_probe(struct mipi_dsi_device *dsi)
{
	struct device *dev = &dsi->dev;
	struct k7_panel *panel;
	int ret;

	panel = devm_kzalloc(dev, sizeof(*panel), GFP_KERNEL);
	if (!panel)
		return -ENOMEM;

	panel->desc = of_device_get_match_data(dev);
	if (!panel->desc)
		return -ENODEV;

	panel->vddio = devm_regulator_get(dev, "vddio");
	if (IS_ERR(panel->vddio)) {
		dev_err(dev, "Failed to get vddio regulator: %ld\n", PTR_ERR(panel->vddio));
		return PTR_ERR(panel->vddio);
	}

	panel->vci = devm_regulator_get(dev, "vci");
	if (IS_ERR(panel->vci)) {
		dev_err(dev, "Failed to get vci regulator: %ld\n", PTR_ERR(panel->vci));
		return PTR_ERR(panel->vci);
	}

	panel->reset_gpio = devm_gpiod_get(dev, "reset", GPIOD_OUT_LOW);
	if (IS_ERR(panel->reset_gpio)) {
		dev_err(dev, "Failed to get reset GPIO: %ld\n", PTR_ERR(panel->reset_gpio));
		return PTR_ERR(panel->reset_gpio);
	}

	panel->dsi = dsi;
	mipi_dsi_set_drvdata(dsi, panel);

	/*
	 * Older API: drm_panel_init only takes panel,
	 * then we assign dev and funcs manually.
	 */
	drm_panel_init(&panel->panel);
	panel->panel.dev = dev;
	panel->panel.funcs = &k7_panel_funcs;

	drm_panel_add(&panel->panel);

	dsi->lanes = panel->desc->lanes;
	dsi->format = MIPI_DSI_FMT_RGB888;
	dsi->mode_flags = MIPI_DSI_MODE_VIDEO | MIPI_DSI_MODE_VIDEO_BURST |
			  MIPI_DSI_MODE_LPM;

	ret = mipi_dsi_attach(dsi);
	if (ret < 0) {
		dev_err(dev, "DSI attach failed: %d\n", ret);
		drm_panel_remove(&panel->panel);
		return ret;
	}

	return 0;
}

static int k7_panel_remove(struct mipi_dsi_device *dsi)
{
	struct k7_panel *panel = mipi_dsi_get_drvdata(dsi);

	mipi_dsi_detach(dsi);
	drm_panel_remove(&panel->panel);
	return 0;
}

static const struct of_device_id k7_of_match[] = {
	{ .compatible = "xiaomi,k7-38-0c-0a-panel", .data = &k7_0a_desc },
	{ .compatible = "xiaomi,k7-38-0c-0b-panel", .data = &k7_0b_desc },
	{ /* sentinel */ }
};
MODULE_DEVICE_TABLE(of, k7_of_match);

static struct mipi_dsi_driver k7_panel_driver = {
	.driver = {
		.name = "panel-xiaomi-k7",
		.of_match_table = k7_of_match,
	},
	.probe = k7_panel_probe,
	.remove = k7_panel_remove,
};
module_mipi_dsi_driver(k7_panel_driver);

MODULE_AUTHOR("Your Name");
MODULE_DESCRIPTION("Xiaomi K7 DSI Panel Driver");
MODULE_LICENSE("GPL");
