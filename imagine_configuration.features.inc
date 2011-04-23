<?php
/**
 * @file
 * imagine_configuration.features.inc
 */

/**
 * Implementation of hook_ctools_plugin_api().
 */
function imagine_configuration_ctools_plugin_api() {
  list($module, $api) = func_get_args();
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => 1);
  }
}

/**
 * Implementation of hook_node_info().
 */
function imagine_configuration_node_info() {
  $items = array(
    'page' => array(
      'name' => t('Page'),
      'base' => 'node_content',
      'description' => t('Add a static page of content to your site and place it in the main menu if desired.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  return $items;
}
