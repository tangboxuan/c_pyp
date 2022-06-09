#include <string.h>
#include "ann.h"

/* Creates and returns a new ann. */
ann_t *ann_create(int num_layers, int *layer_outputs)
{
  /**** PART 2 - QUESTION 1 ****/
  ann_t *ann = malloc(sizeof(ann_t));
  if (ann == NULL) {
    return NULL;
  }
  layer_t *prev = NULL;
  for (int i = 0; i < num_layers; i++) {
    layer_t *layer = layer_create();
    if (layer == NULL) {
      return NULL;
    }
    if (layer_init(layer, layer_outputs[i], prev)) {
      return NULL;
    }
    if (i == 0) {
      ann->input_layer = layer;
    } else {
      prev->next = layer;
    }
    if (i == num_layers - 1) {
      ann->output_layer = layer;
    }
    prev = layer;
  }
  return ann;
  /* 4 MARKS */
}

/* Frees the space allocated to ann. */
void ann_free(ann_t *ann)
{
  /**** PART 2 - QUESTION 2 ****/
  if (ann != NULL) {
    layer_t *layer = ann->input_layer;
    while (layer != NULL) {
      layer_t *next = layer->next;
      layer_free(layer);
      layer = next;
    }
    free(ann);
  }
  /* 2 MARKS */
}

/* Forward run of given ann with inputs. */
void ann_predict(ann_t const *ann, double const *inputs)
{
  /**** PART 2 - QUESTION 3 ****/
  layer_t *layer = ann->input_layer;
  memcpy(layer->outputs, inputs, layer->num_outputs * sizeof(double));
  layer = layer->next;
  while(layer != NULL) {
    layer_compute_outputs(layer);
    layer = layer->next;
  }
  /* 2 MARKS */
}

/* Trains the ann with single backprop update. */
void ann_train(ann_t const *ann, double const *inputs, double const *targets, double l_rate)
{
  /* Sanity checks. */
  assert(ann != NULL);
  assert(inputs != NULL);
  assert(targets != NULL);
  assert(l_rate > 0);

  /* Run forward pass. */
  ann_predict(ann, inputs);

  /**** PART 2 - QUESTION 4 ****/
  layer_t *layer = ann->output_layer;
  for (int i = 0; i < layer->num_outputs; i++) {
    layer->deltas[i] = sigmoidprime(layer->outputs[i]) * (targets[i] - layer->outputs[i]);
  }
  while(layer != ann->input_layer) {
    layer_compute_deltas(layer);
    layer = layer->prev;
  }
  layer = ann->output_layer;
  while(layer != ann->input_layer) {
    layer_update(layer, l_rate);
    layer = layer->prev;
  }
  /* 3 MARKS */
}
