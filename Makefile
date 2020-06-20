build_frontend:
	cd frontend && yarn build

compress_frontend:
	cd frontend && yarn export

build_firmware:
	source ./venv/bin/activate && cd firmware && platformio run

upload_firmware:
	source ./venv/bin/activate && cd firmware && platformio run --target upload

upload_fs: build_frontend compress_frontend
	source ./venv/bin/activate && cd firmware && platformio run --target uploadfs