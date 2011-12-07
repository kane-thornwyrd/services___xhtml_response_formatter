<?php

/**
 * @file
 * Where reside the XHtmlFormatView, response format for services,
 * class implementation.
 */
class XHtmlFormatView extends RESTServerView {

  /**
   * Function called by RESTServer to display the ressource.
   * @return string
   *   The rendered xHTML.
   */
  public function render() {
    $test = $this->model;
    return $this->renderXHtml($this->model);
  }

  /**
   * Specific sub rendering function
   *
   * @param mixed $content
   * is the thing to render.
   *
   * @return string
   *   The rendered xHTML.
   */
  protected function renderXHtml($content) {
    // TODO Better check if the stdClass we try to render is a node for real.
    $out = '';
    if (is_array($content)) {
      foreach ($content as $element) {
        if ($this->isAstdClass($element)) {
          $out .= $this->renderstdClass($element);
        }
        else {
          $out .= print_r($element, TRUE);
        }
      }
    }
    elseif ($this->isAstdClass($content)) {
      $out = $this->renderstdClass($$content);
    }
    else {
      $out = print_r($content, TRUE);
    }
    return $out;
  }

  /**
   * Check if $var is a stdClass in the PHP 5.2 and PHP 5.3 styles.
   *
   * @param mixed $var
   * is the one we test.
   *
   * @return bool
   *   Is $var a stdClass
   */
  protected function isAstdClass($var) {
    return (version_compare(PHP_VERSION, '5.3.0') >= 0)
      ? is_a($var, 'stdClass')
      : ($var instanceof stdClass);
  }

  /**
   * In this context we can assume that a stdClass is in fact a node.
   *
   * @param stdClass $content is the assumed node to render.
   *
   * @return string
   *   The rendered xHTML.
   */
  protected function renderstdClass(stdClass $content) {
    return drupal_render(node_view($content));
  }

}
