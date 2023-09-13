from django.db import models
from django.core.validators import MinValueValidator, MaxValueValidator
from django.contrib.auth.models import User

class Survey(models.Model):
    survey_id = models.AutoField(primary_key=True)
    title = models.CharField(max_length=255)
    description = models.TextField()
    survey_id = models.IntegerField(default=0)

class Question(models.Model):
    survey = models.ForeignKey(Survey, on_delete=models.CASCADE)

    # Create 20 question answer fields with unique names
    answer_fields = {}
    for i in range(1, 21):
        field_name = f'question{i}_answer'
        answer_fields[field_name] = models.PositiveIntegerField(
            validators=[
                MinValueValidator(1, "Answer must be between 1 and 10"),
                MaxValueValidator(10, "Answer must be between 1 and 10")
            ],
            null=True,  # Allow blank answers
            blank=True,
        )

    # Use locals() to dynamically create the fields
    locals().update(answer_fields)

    def __str__(self):
        return f'Question {self.id}'

class UserResponse(models.Model):
    user = models.ForeignKey(User, on_delete=models.CASCADE)
    survey = models.ForeignKey(Survey, on_delete=models.CASCADE)
    
    # Create 20 response fields with unique names
    response_fields = {}
    for i in range(1, 21):
        field_name = f'question{i}_response'
        response_fields[field_name] = models.PositiveIntegerField(
            validators=[
                MinValueValidator(1, "Response must be between 1 and 10"),
                MaxValueValidator(10, "Response must be between 1 and 10")
            ],
            null=True,  # Allow blank responses
            blank=True,
        )

    # Use locals() to dynamically create the fields
    locals().update(response_fields)

    def __str__(self):
        return f'Responses for User {self.user.username} in Survey {self.survey.title}'
