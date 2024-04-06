"""
Download Glassdoor Interview Experiences and convert them to Markdown!

This is the GraphQL query that was used to generate the JSON data:

query InterviewsPageGraphQueryIG(
  $sort: InterviewsSortOrderEnum
  $employerId: Int!
  $goc: Int
  $jobTitle: JobTitleIdent
  $location: LocationIdent
  $outcome: [InterviewOutcomeEnum]
  $page: Int!
  $itemsPerPage: Int!
  $tldId: Int!
  $profileId: Int
) {
  employerInterviews: employerInterviewsIG(
    employerInterviewsInput: {
      sort: $sort
      employer: { id: $employerId }
      jobTitle: $jobTitle
      goc: { sgocId: $goc }
      location: $location
      outcomes: $outcome
      page: { num: $page, size: $itemsPerPage }
    }
  ) {
    currentPageNum
    totalNumberOfPages
    totalInterviewCount
    filteredInterviewCount
    employer {
      bestPlacesToWork(onlyCurrent: true) {
        bannerImageUrl
        id
        isCurrent
        timePeriod
        __typename
      }
      bestProfile {
        id
        __typename
      }
      ceo {
        id
        name
        __typename
      }
      counts {
        pollCount
        __typename
      }
      employerManagedContent(
        parameters: [{ employerId: $employerId, divisionProfileId: $profileId }]
      ) {
        isContentPaidForTld
        __typename
      }
      id
      largeLogoUrl: squareLogoUrl(size: LARGE)
      links {
        jobsUrl
        reviewsUrl
        faqUrl
        __typename
      }
      regularLogoUrl: squareLogoUrl(size: REGULAR)
      shortName
      squareLogoUrl
      website
      __typename
    }
    interviewExperienceCounts {
      type
      count
      __typename
    }
    interviewObtainedChannelCounts {
      type
      count
      __typename
    }
    interviewOutcomeCounts {
      type
      count
      __typename
    }
    interviewExperienceSum
    difficultySubmissionCount
    difficultySum
    newestReviewDate
    interviewQuestionCount
    overallDurationDaysSum
    overallDurationDaysCount
    content: interviews {
      id
      advice
      countHelpful
      countNotHelpful
      currentJobFlag
      declinedReason
      difficulty
      durationDays
      employerResponses {
        id
        response
        responseDateTime
        __typename
      }
      experience
      featured
      interviewDateTime
      jobTitle {
        text
        __typename
      }
      location {
        type
        name
        __typename
      }
      negotiationDescription
      otherSource
      otherSteps
      outcome
      processDescription
      reviewDateTime
      source
      userQuestions {
        answerCount
        id
        question
        __typename
      }
      __typename
    }
    popularJobTitlesInterviews {
      jobTitle
      count
      __typename
    }
    queryLocation {
      id
      type
      shortName
      longName
      __typename
    }
    __typename
  }
  interviewCountForTldAndEmployer: interviewCountForTldAndEmployerIG(
    employerInterviewInsightsRequest: {
      employerId: $employerId
      tldId: $tldId
      applyTldFilter: true
    }
  )
}

"""

import json
import textwrap

from pathlib import Path

def main(fp):
    with open(fp) as f:
        data = json.load(f)

    # Extract this key from json:
    interviews = data[0]['data']['employerInterviews']['content']

    # Sort interviews on interviewDateTime
    interviews = sorted(interviews, key=lambda x: (x['interviewDateTime'] is None, x['interviewDateTime']))

    for iv in interviews:
        questions = [q["question"] for q in iv['userQuestions']]
        questions = "\n".join(questions)

        md = f"""
        ## {iv['jobTitle']['text']} - {(iv.get('location', {}) or {}).get('name', '')} - {iv['interviewDateTime'] or ''}

        Description: 
            {iv['processDescription']}

        Questions: 
            {questions}

        ----"""
        md = textwrap.dedent(md)
        print(md)

if __name__ == '__main__':
    import sys

    if len(sys.argv) != 2:
        print(f'usage: {sys.argv[0]} <file>')
        sys.exit(1)

    main(Path(sys.argv[1]).expanduser())
