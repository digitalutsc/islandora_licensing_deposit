<?php

/**
 * @file
 *  Deposit and License Form
 */

/**
 * Deposit and License Form
 *
 * @param array $form
 *   The Drupal form.
 * @param array $form_state
 *   The Drupal form state.
 * @param @args
 *
 * @return array
 *   A Drupal form definition.
 */


function islandora_licensing_deposit_form(array $form, array &$form_state, $args) {
  $selected_collection_name = $args;

  $selected_collection_url = get_license_deposit_url($selected_collection_name);

  $form = array();
  $form['islandora_licensing_deposit_file_form'] = array(
    '#type' => 'textfield',
    '#title' => 'Deposit Agreement',
    '#description' => t('Deposit and Licensing Agreement. Please read carefully.'),
    '#rows' => 10,
    '#default_value' => $selected_collection_url,
    '#resizable' => TRUE,
  );

  $form['islandora_licensing_deposit_file_form_read'] = array(
    '#type' => 'link',
    '#title' => t('Read Licensing/Deposit Agreement'),
    '#href' => $selected_collection_url,
    '#attributes' => array(
      'target' => "_blank",
    ),
  );

  $form['#attributes']['target'] = '_top';

  $form["deposit_check"] = array(
    '#title' => 'Click here to agree:',
    '#type' => 'checkbox',
    '#required' => TRUE,
  );

  $form_state['islandora']['shared_storage']['agreement_url'] = $selected_collection_url;

  return $form;
}

function get_license_deposit_url($selected_collection_name) {
  $collections_url_map = variable_get('islandora_licensing_deposit');
  $selected_collection_url = isset($collections_url_map["all"]["url"]) ? $collections_url_map["all"]["url"] : "NotSet";

  foreach ($collections_url_map as $key => $value) {
    $collection_name = $collections_url_map[$key]['collection'];
    $collection_url = $collections_url_map[$key]['url'];
    if ($collection_name == $selected_collection_name) {
      $selected_collection_url = $collection_url;
      break;
    }
  }
  return $selected_collection_url;
}


