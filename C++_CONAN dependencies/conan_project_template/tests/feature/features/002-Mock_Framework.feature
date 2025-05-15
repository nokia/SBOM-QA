# language: en
Feature: Mock Framework feature
  As a developer writting feature tests
  I want to use a Mock Framwork
  In order to writte tests independent from external dependencies

Scenario: Set Expectations on a Mock
  Given a mock class with method foo
  And the tests expects that foo is called once
  When foo is called on the mock
  Then the test should pass
