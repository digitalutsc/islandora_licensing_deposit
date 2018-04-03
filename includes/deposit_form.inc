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
  $content_model = $args;
  $form = array();
  $form['islandora_licensing_deposit_file_form'] = array(
    '#type' => 'textarea',
    '#title' => 'Deposit Agreement',
    '#description' => t('Deposit and Licensing Agreement. Please read carefully.'),
    '#rows' => 10,
    '#default_value' => $content_model,
    '#resizable' => TRUE,
  );

  $form["deposit_check"] = array(
    '#title' => 'Click here to agree:',
    '#type' => 'checkbox',
    '#required' => TRUE,
  );

  return $form;
}


