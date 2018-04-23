<?php

/**
 * @file
 * Handles the display/submission of the admin settings form for this module.
 */

/**
 * Defines the admin settings form.
 *
 * @param array $form
 *   The Drupal form definition.
 * @param array $form_state
 *   The Drupal form state.
 *
 * @return array
 *   The Drupal form definition.
 */
function islandora_licensing_deposit_admin(array $form, array &$form_state) {


   $table_info = variable_get('islandora_licensing_deposit_table_wrapper', FALSE)["table"]["values"];
   $table_info_debug = print_r(variable_get('islandora_licensing_deposit_table_wrapper', FALSE)["table"]["values"], true);

   $max_rows = sizeof($table_info);
   if ($max_rows == 0){
     $max_rows = 1;
   }

  $form['islandora_licensing_deposit'] = array(
    '#type' => 'fieldset',
    '#title' => t('Islandora Licensing and Deposit Configurations'),
    '#collapsible' => TRUE,
    '#group' => 'additional_settings',
  );
  $form['islandora_licensing_deposit']['islandora_licensing_deposit_table_wrapper'] = array(
    '#type' => 'container',
    '#tree' => TRUE,
    '#prefix' => '<div id="islandora_licensing_deposit_table_wrapper">',
    '#suffix' => '</div>',
  );

  // table header
  $header = array(
    'collection' => array('data' => 'Collection'),
    'url' => array('data' => 'url'),
  );

  // check how many empty rows have to be rendered
  // check if button "add item" has been clicked
  if (!isset($form_state['num_new_items'])) {
    $form_state['num_new_items'] = $max_rows;
  }

  // table info
  for ($i = 0; $i < $form_state['num_new_items']; $i++) {

    $row_info = $table_info["row_item_" . $i];
    $collection = $row_info["collection"];
    $url = $row_info["url"];

    $collection = array(
      '#type' => 'textfield',
      '#default_value' => $collection,
    );

    $url_obj = array(
      '#type' => 'textfield',
      '#default_value' => $url,
    );

    $rows['row_item_'.$i] = array(
      'data' => array(
        'collection' => array('data' => &$collection),
        'url' => array('data' => &$url_obj),
      ),
    );
    $data_to_send['row_item_'.$i] = array(
      'collection' => &$collection,
      'url' => &$url_obj,
    );
    unset($collection);
    unset($url_obj);
  }

  // generate table
  $form['islandora_licensing_deposit']['islandora_licensing_deposit_table_wrapper']['table'] = array(
    '#tree' => TRUE,
    '#theme' => 'table',
    '#header' => $header,
    'values' => $data_to_send,
    '#rows' => &$rows,
  );

  $form['islandora_licensing_deposit']['add'] = array(
    '#type' => 'button',
    '#value' => 'Add Item',
    '#href' => '',
    '#ajax' => array(
      'callback' => 'mymodule_add_item_callback',
      'wrapper' => 'islandora_licensing_deposit_table_wrapper', // wrapper is unique reference to DIV ID, don't forget about it
    ),
  );

  $form['islandora_licensing_deposit']['del'] = array(
    '#type' => 'button',
    '#value' => 'Delete Items',
    '#href' => '',
    '#submit' => array('remove_layers_submit'),
    '#ajax' => array(
      'callback' => 'mymodule_del_items_callback',
      'wrapper' => 'islandora_licensing_deposit_table_wrapper', // wrapper is unique reference to DIV ID, don't forget about it
    ),
  );

  // increment number of new items
  $form_state['num_new_items']++;
  $form = system_settings_form($form);
  return $form;
}

function mymodule_del_items_callback($form, &$form_state) {
  // this callback MUST return wrapped table rows
  // right now entire table will be rebuilt
  return $form['islandora_licensing_deposit'];
}


function mymodule_add_item_callback($form, &$form_state) {
  // this callback MUST return wrapped table rows
  // right now entire table will be rebuilt
  return $form['islandora_licensing_deposit']['islandora_licensing_deposit_table_wrapper'];
}