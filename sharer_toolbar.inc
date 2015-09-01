<?php

/**
 * @file sharer_toolbar.inc
 * Helper functions
 */

/**
 * List all available sharers by invoking:
 * - hook_sharer_toolbar_available_sharer()
 * - hook_sharer_toolbar_available_sharer_alter()
 */
function _sharer_toolbar_get_available_sharers() {
  $available_sharers = module_invoke_all('sharer_toolbar_available_sharer');
  drupal_alter('sharer_toolbar_available_sharer', $available_sharers);

  // And return them
  return $available_sharers;
}

/**
 * List all available sharers,
 * ordered by config form weight if available
 */
function _sharer_toolbar_get_ordered_available_sharers() {
  $ordered_sharers = array();

  // Get all available sharers
  $available_sharers = _sharer_toolbar_get_available_sharers();

  // Generate ordered list if sharers order is already defined
  $sharers_order = variable_get('sharer_toolbar_sharers_order', array());
  $existing_sharers = array();
  if (!empty($sharers_order)) {

    // List already ordered sharers
    foreach ($sharers_order as $weight => $sid) {
      if (isset($available_sharers[$sid])) {
        $ordered_sharers[$weight] = $available_sharers[$sid];
        $existing_sharers[] = $sid;
      }
    }

    // Add new sharers
    $weight++;
    foreach ($available_sharers as $sid => $sharer) {
      if (!in_array($sid, $existing_sharers)) {
        $ordered_sharers[$weight] = $sharer;
        $weight++;
      }
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


/**
 * Replace tokens with correct value in pattern URL
 */
function _sharer_toolbar_generate_sharer_url(&$sharer_url, $variables) {
  global $base_root;

  // URL replacement
  $node_url = url('node/' . $variables['nid'], array(
    'language' => (object) array('language' => $variables['language']),
  ));
  $sharer_url = str_replace('[:shared_url:]', $base_root . $node_url, $sharer_url);

  // Title replacement
  $sharer_url = str_replace('[:shared_title:]', $variables['title'], $sharer_url);

  // Source replacement
  $sharer_url = str_replace('[:shared_source:]', variable_get('site_name', ''), $sharer_url);

  // Summary replacement
  $truncate_summary = '';
  if (isset($variables['node']->field_catchline) && !empty($variables['node']->field_catchline)) {
    if (isset($variables['node']->field_catchline[LANGUAGE_NONE])) {
      $summary = $variables['node']->field_catchline[LANGUAGE_NONE][0]['safe_value'];
    }
    else {
      $summary = $variables['node']->field_catchline[0]['safe_value'];
    }
    $truncate_summary = truncate_utf8(drupal_html_to_text($summary), 200, TRUE, $add_ellipsis = TRUE);
  }
  $sharer_url = str_replace('[:shared_summary:]', $truncate_summary, $sharer_url);

  // Replace spaces by %20 to be consistent with w3c
  $sharer_url = str_replace(' ', '%20', $sharer_url);
}
