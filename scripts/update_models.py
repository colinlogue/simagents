import os

def get_model_labels():
	# returns list of all subdirectories in models/
	return [x for x in os.listdir('models') if os.path.isdir(os.path.join('models', x))]

def update_models():
	labels = get_model_labels()

	# add the list of models into the template
	with open('scripts/templates/models_h_template.h', 'r') as template_f:
		template = template_f.read()

	add_labels = ''
	for label in labels:
		add_labels += 'model_t *build_<<LABEL>>(void init_f(sim_t), void step_f(sim_t), size_t);\n'.replace('<<LABEL>>', label)

	# write to destination file
	with open('models/models.h', 'w') as dest_f:
		dest_f.write(template.replace('<<MODELS>>', add_labels))


if __name__ == "__main__":
	update_models()