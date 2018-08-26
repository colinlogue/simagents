import os


def update_models():
	# get a list of all subdirectories in models/
	labels = [x for x in os.listdir('models') if os.path.isdir(os.path.join('models', x))]

	# add the list of models into the template
	with open('scripts/models_h_template.h', 'r') as template_f:
		template = template_f.read()

	add_labels = ''
	for label in labels:
		add_labels += f'model_t {label};\n'

	# write to destination file
	with open('models/models.h', 'w') as dest_f:
		dest_f.write(template)

if __name__ == "__main__":
	update_models()