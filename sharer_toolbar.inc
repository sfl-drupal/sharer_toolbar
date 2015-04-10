<?php

/**
 * @file sharer_toolbar.inc
 * Helper functions
 */

/**
 * List all available environments,
 * ordered by config form weight if available
 */
function _sharer_toolbar_get_ordered_available_sharers() {
  $ordered_sharers = array();

  // List all available sharers by invoking:
  // - hook_sharer_toolbar_available_sharer()
  // - hook_sharer_toolbar_available_sharer_alter()
  $available_sharers = module_invoke_all('sharer_toolbar_available_sharer');
  drupal_alter('sharer_toolbar_available_sharer', $available_sharers);

  // Generate ordered list if sharers order is already defined
  $sharers_order = variable_get('sharer_toolbar_sharers_order', array());
  if (!empty($sharers_order)) {
    foreach ($sharers_order as $weight => $sid) {
      $ordered_sharers[$weight] = $available_sharers[$sid];
    }
  }

  // Else, keep default order and index sharers array numerically
  else {
    $ordered_sharers = array_values($available_sharers);
  }


  // Return ordered sharers
  ksort($ordered_sharers);
  return $ordered_sharers;
}
