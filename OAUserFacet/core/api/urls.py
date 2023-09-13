from django.urls import path, include
from rest_framework.routers import DefaultRouter
from . import views

# Create a router and register the viewsets.
router = DefaultRouter()
router.register(r'surveys', views.SurveyListViewSet)

urlpatterns = [

    # Include the URLs for survey viewset
    path('', include(router.urls)),

    # Create a survey
    path('surveys/create/', views.CreateSurveyView.as_view(), name='create-survey'),

    # Submit a response for a survey
    path('surveys/<int:survey_id>/submit-response/', views.SubmitResponseView.as_view(), name='submit-response'),

    # Route for calculate_similarity
    path('similarity/calculate_similarity/', views.SimilarityViewSet.as_view({'get': 'calculate_similarity'}), name='calculate_similarity'),
]

