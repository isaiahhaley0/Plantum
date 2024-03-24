import os
import matplotlib.pyplot as plt
import numpy as np
import PIL
import tensorflow as tf
from pathlib import Path
from tensorflow import keras
from tensorflow.keras import layers
from tensorflow.keras.models import Sequential





class basic_trainer:
    def __init__(self, directory, model_name):
        self.__directory = directory
        self.__name = model_name

    def create_model(self):
        print("Starting")

        dataset_dir = sef.__directory
        data_dir = Path(dataset_dir).with_suffix('')
        image_count = len(list(data_dir.glob('*/*.jpg')))
        print(image_count)
        batch_size = 32
        img_height = 180
        img_width = 180
        # create datasets
        # training
        train_ds = tf.keras.utils.image_dataset_from_directory(data_dir, validation_split=0.2, subset="training",
                                                               seed=123, image_size=(img_height, img_width),
                                                               batch_size=batch_size)

        # validation
        val_ds = tf.keras.utils.image_dataset_from_directory(
            data_dir,
            validation_split=0.2,
            subset="validation",
            seed=123,
            image_size=(img_height, img_width),
            batch_size=batch_size)

        class_names = train_ds.class_names
        print(class_names)

        # set up performance

        AUTOTUNE = tf.data.AUTOTUNE

        train_ds = train_ds.cache().shuffle(1000).prefetch(buffer_size=AUTOTUNE)
        val_ds = val_ds.cache().prefetch(buffer_size=AUTOTUNE)

        # standardize
        normalization_layer = layers.Rescaling(1. / 255)

        normalized_ds = train_ds.map(lambda x, y: (normalization_layer(x), y))
        image_batch, labels_batch = next(iter(normalized_ds))
        first_image = image_batch[0]
        # Notice the pixel values are now in `[0,1]`.
        print(np.min(first_image), np.max(first_image))

        # creating model
        num_classes = len(class_names)

        model = Sequential([
            layers.Rescaling(1. / 255, input_shape=(img_height, img_width, 3)),
            layers.Conv2D(16, 3, padding='same', activation='relu'),
            layers.MaxPooling2D(),
            layers.Conv2D(32, 3, padding='same', activation='relu'),
            layers.MaxPooling2D(),
            layers.Conv2D(64, 3, padding='same', activation='relu'),
            layers.MaxPooling2D(),
            layers.Flatten(),
            layers.Dense(128, activation='relu'),
            layers.Dense(num_classes)
        ])

        # compile model
        model.compile(optimizer='adam',
                      loss=tf.keras.losses.SparseCategoricalCrossentropy(from_logits=True),
                      metrics=['accuracy'])

        model.summary()

        # train
        print("Training")
        epochs = 15
        checkpoint_path = "I:/repos/Plantum/Training/Models/"+self.__name+".weights.h5"
        checkpoint_dir = os.path.dirname(checkpoint_path)
        cp_callback = tf.keras.callbacks.ModelCheckpoint(filepath=checkpoint_path,
                                                         save_weights_only=True,
                                                         verbose=1)
