<?php

/**
 * implementation of hook_panels_layouts()
 */
// Plugin definition
$plugin = array(
  'title' => t('Imagine Front'),
  'category' => t('Imagine Layouts'),
  'icon' => 'imagine_front.png',
  'theme' => 'imagine_configuration_imagine_front',
  'css' => 'imagine_front.css',
  'regions' => array(
    'top' => t('Top row'),
    'left' => t('Left column'),
    'right' => t('Right column'),
    'bottom' => t('Bottom row'),
  ),
);
