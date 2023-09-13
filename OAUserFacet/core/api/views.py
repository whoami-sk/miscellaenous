from rest_framework.views import APIView
from .models import Survey, UserResponse
from .serializers import SurveySerializer, QuestionSerializer, UserResponseSerializer
from rest_framework import viewsets, status
from rest_framework.decorators import action
from rest_framework.response import Response
import numpy as np  # Import NumPy for similarity calculation

from .models import UserResponse

class SimilarityViewSet(viewsets.ViewSet):
    @action(detail=False, methods=['get'])
    def calculate_similarity(self, request):
        user_responses = UserResponse.objects.all()

        # Extract responses and user IDs
        responses = [list(response.get_responses()) for response in user_responses]
        user_ids = [response.user_id for response in user_responses]

        # Calculate similarity (you can use a similarity metric like cosine similarity)
        similarity_matrix = np.dot(responses, np.transpose(responses))

        # Convert the similarity matrix to a list of dictionaries
        similarity_data = []
        for i, user_id in enumerate(user_ids):
            similarity_data.append({
                'user_id': user_id,
                'similarity_scores': similarity_matrix[i].tolist()
            })

        return Response(similarity_data, status=status.HTTP_200_OK)


class CreateSurveyView(APIView):
    def post(self, request, format=None):
        # Deserialize the incoming JSON data
        serializer = SurveySerializer(data=request.data)

        if serializer.is_valid():
            # Create the survey instance
            survey = serializer.save()

            # Create 20 question instances associated with the survey
            for i in range(1, 21):
                question_data = {'survey': survey.id}
                question_data.update({f'question{i}_answer': None})
                question_serializer = QuestionSerializer(data=question_data)
                if question_serializer.is_valid():
                    question_serializer.save()
                else:
                    # Handle invalid question data here, if needed
                    pass

            return Response(serializer.data, status=status.HTTP_201_CREATED)
        return Response(serializer.errors, status=status.HTTP_400_BAD_REQUEST)


class SurveyListViewSet(viewsets.ModelViewSet):
    queryset = Survey.objects.all()
    serializer_class = SurveySerializer

class SubmitResponseView(APIView):
    def post(self, request, survey_id, format=None):
        try:
            survey = Survey.objects.get(pk=survey_id)
        except Survey.DoesNotExist:
            return Response({"error": "Survey does not exist"}, status=status.HTTP_404_NOT_FOUND)

        serializer = UserResponseSerializer(data=request.data)
        if serializer.is_valid():
            
            user = request.user
            existing_response = UserResponse.objects.filter(user=user, survey=survey).first()
            if existing_response:
                return Response({"error": "User has already submitted a response for this survey"},
                                status=status.HTTP_400_BAD_REQUEST)

            # Create the user's response for the survey
            response = serializer.save(user=user, survey=survey)

            return Response(serializer.data, status=status.HTTP_201_CREATED)
        return Response(serializer.errors, status=status.HTTP_400_BAD_REQUEST)
