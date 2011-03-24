<?php
/**
 * @file
 * imagine_configuration.features.user_role.inc
 */

/**
 * Implementation of hook_user_default_roles().
 */
function imagine_configuration_user_default_roles() {
  $roles = array();

  // Exported role: guild council
  $roles['guild council'] = array(
    'name' => 'guild council',
    'weight' => '4',
  );

  // Exported role: guild member
  $roles['guild member'] = array(
    'name' => 'guild member',
    'weight' => '3',
  );

  // Exported role: image technician
  $roles['image technician'] = array(
    'name' => 'image technician',
    'weight' => '5',
  );

  return $roles;
}
