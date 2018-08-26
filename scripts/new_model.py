from update_models import update_models, get_model_labels
import sys
import os

if __name__ == "__main__":
	labels = get_model_labels()
	new_label = sys.argv[1]
	assert(new_label not in labels)

	# make new model directory
	# reminder: paths are relative to project root directory
	os.mkdir(os.path.join('models', new_label))

	# create template files
	# get list of all files in template folder
	template_fps = [x for x in os.listdir('scripts/templates/new_model')]
	template_dir = 'scripts/templates/new_model'
	target_dir = os.path.join('models', new_label)
	for template_fp in template_fps:
		with open(os.path.join(template_dir, template_fp), 'r') as template_f:
			target_fp = template_fp.replace('_template', '')
			with open(os.path.join(target_dir, target_fp), 'w') as tar_f:
				tar_f.write(template_f.read().replace('<<LABEL>>', new_label))
