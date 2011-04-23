<?php

/**
 * Plugins are described by creating a $plugin array which will be used
 * by the system that includes this file.
 */

$plugin = array(
  'title' => t('Create Node: Publish Options'),
  'description' => t('Allows the creation of a particular node type and exposes its default publishing options.  This circumvents the typical drupal access controls on node creation.'),
  'content form' => 'imagine_configuration_node_create_pubopt_content_form',
  'content form submit' => 'imagine_configuration_node_create_pubopt_content_form_submit',
  'render' => 'imagine_configuration_node_create_pubopt_render_page',
  'form alter' => 'imagine_configuration_node_create_pubopt_form_alter',
);


function imagine_configuration_node_create_pubopt_content_form($form, $form_state, $cache = NULL) {
  if (isset($form_state['page']->handlers[$form_state['handler_id']]->conf['node_types'])) {
    $default = $form_state['page']->handlers[$form_state['handler_id']]->conf['node_types'];
  }
  elseif (isset($cache->handlers[$form_state['handler_id']]->conf['node_types'])) {
    $default = $cache->handlers[$form_state['handler_id']]->conf['node_types'];
  }
  else {
    $default = '';
  }
  $options = node_type_get_names();
  $form['node_types'] = array(
    '#type' => 'radios',
    '#title' => t('Select the node type you would like to create'),
    '#required' => TRUE,
    '#options' => $options,
    '#default_value' => $default,
  );

  if (isset($form_state['page']->handlers[$form_state['handler_id']]->conf['publishing_options'])) {
    $sub = $form_state['page']->handlers[$form_state['handler_id']]->conf['publishing_options'];
  }
  elseif (isset($cache->handlers[$form_state['handler_id']]->conf['publishing_options'])) {
    $sub = $cache->handlers[$form_state['handler_id']]->conf['publishing_options'];
  }
  else {
    $sub = 0;
  }
  $form['publishing_options'] = array(
    '#type' => 'radios',
    '#title' => t('Publishing Options'),
    '#description' => t('Choose whethere this node type is published or unpublished by default.'),
    '#options' => array(
      t('Unpublished'),
      t('Published'),
    ),
    '#default_value' => $sub ? $sub : 1,
  );

  return $form;
}

function imagine_configuration_node_create_pubopt_content_form_submit($form, &$form_state) {
  $cache = context_admin_get_page_cache($form_state['page']->subtask_id);
  if (!is_null($form_state['handler_id'])) {
    $form_state['page']->handlers[$form_state['handler_id']]->conf['node_types'] = $form_state['values']['node_types'];
  }
  else {
    $form_state['page']->new_handler->conf['node_types'] = $form_state['values']['node_types'];
  }
  if ($form_state['values']['publishing_options']) {
    if (!is_null($form_state['handler_id'])) {
      $form_state['page']->handlers[$form_state['handler_id']]->conf['publishing_options'] = $form_state['values']['publishing_options'];
    }
    else {
      $form_state['page']->new_handler->conf['publishing_options'] = $form_state['values']['publishing_options'];
    }
  }
  context_admin_set_page_cache($form_state['page']->subtask_id, $form_state['page']);
  return $form_state;
}

function imagine_configuration_node_create_pubopt_render_page($handler, $base_contexts, $args, $test = TRUE) {
  $type = $handler->conf['node_types'];
  module_load_include('inc', 'node', 'node.pages');

  return node_add($type);
}

function imagine_configuration_node_create_pubopt_form_alter(&$form, $form_state, $form_id) {
  $page = page_manager_get_current_page();
  if ($page && (isset($page['handler']->conf['context_admin_options']) && $page['handler']->conf['context_admin_options'] == 'node_create_pubopt')) {
    $type = isset($page['handler']->conf['node_types']) ? $page['handler']->conf['node_types'] : '';
    if ($form_id == $type . '_node_form') {
      $form['options']['status']['#default_value'] = $page['handler']->conf['publishing_options'];
    }
  }
}
